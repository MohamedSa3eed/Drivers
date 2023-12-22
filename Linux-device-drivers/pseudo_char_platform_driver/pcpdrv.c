#include "linux/kern_levels.h"
#include "platform_data.h"
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sa3ed");
MODULE_DESCRIPTION("A simple pseudo platform driver");

#define MAX_DEVICES 10

struct platform_device_data {
  dev_t devt;                  // device number
  char *buffer;                // buffer to store data
  struct cdev cdev;            // character device
  struct platform_data *pdata; // platform data
};

struct platform_driver_data {
  int total_devices;   // total number of devices
  dev_t devt;          // device base number
  struct class *class; // device class
  struct device *dev;  // device
};

struct platform_driver_data pcpdrv_data;

static int pcpdrv_open(struct inode *inode, struct file *file) {
  printk(KERN_INFO "pcp_open: called\n");
  return 0;
}

static int pcpdrv_release(struct inode *inode, struct file *file) {
  printk(KERN_INFO "pcp_release: called\n");
  return 0;
}

static ssize_t pcpdrv_read(struct file *file, char __user *buf, size_t lbuf,
                           loff_t *ppos) {
  printk(KERN_INFO "pcp_read: called\n");
  return 0;
}

static ssize_t pcpdrv_write(struct file *file, const char __user *buf,
                            size_t lbuf, loff_t *ppos) {
  printk(KERN_INFO "pcp_write: called\n");
  return 0;
}

static loff_t pcpdrv_llseek(struct file *file, loff_t offset, int whence) {
  printk(KERN_INFO "pcp_llseek: called\n");
  return 0;
}

struct file_operations pcpdrv_fops = {
    .owner = THIS_MODULE,
    .open = pcpdrv_open,
    .release = pcpdrv_release,
    .read = pcpdrv_read,
    .write = pcpdrv_write,
    .llseek = pcpdrv_llseek,
};

// get called when a device is detected
static int pcpdrv_probe(struct platform_device *pdev) {
  struct platform_device_data *pdev_data;
  struct platform_data *pdata;
  int ret;

  // get the platform data
  pdata = (struct platform_data *)dev_get_platdata(&pdev->dev);
  if (!pdata) {
    printk(KERN_ERR "%s: failed to get platform data\n", __func__);
    return -EINVAL;
  }

  // allocate memory for the device
  pdev_data = (struct platform_device_data *)devm_kzalloc(
      &pdev->dev, sizeof(struct platform_device_data), GFP_KERNEL);
  if (!pdev_data) {
    printk(KERN_ERR "%s: failed to allocate memory for device\n", __func__);
    return -ENOMEM;
  }
  pdev_data->pdata = (struct platform_data *)devm_kzalloc(
      &pdev->dev, sizeof(struct platform_data), GFP_KERNEL);
  if (!pdev_data->pdata) {
    printk(KERN_ERR "%s: failed to allocate memory for pdata\n", __func__);
    return -ENOMEM;
  }
  pdev_data->pdata->memorySize = pdata->memorySize;
  pdev_data->pdata->serial_number = pdata->serial_number;
  pdev_data->buffer =
      (char *)devm_kzalloc(&pdev->dev, pdata->memorySize, GFP_KERNEL);
  if (!pdev_data->buffer) {
    printk(KERN_ERR "%s: failed to allocate memory for device data\n", __func__);
    return -ENOMEM;
  }

  // set platform device data
  /*pdev->dev.driver_data = pdev_data;*/
  dev_set_drvdata(&pdev->dev, pdev_data);

  // get device number
  pdev_data->devt = pcpdrv_data.devt + pdev->id;

  // initialize character device
  cdev_init(&pdev_data->cdev, &pcpdrv_fops);
  ret = cdev_add(&pdev_data->cdev, pdev_data->devt, 1);
  if (ret < 0) {
    printk(KERN_ERR "%s: failed to add device\n", __func__);
    return ret;
  }

  // create device file
  pcpdrv_data.dev = device_create(pcpdrv_data.class, &pdev->dev,
                                  pdev_data->devt, NULL, "pcp-dev%d", pdev->id);
  if (IS_ERR(pcpdrv_data.dev)) { // Check if device creation failed
    printk(KERN_ERR "%s: Device file creation failed\n", __func__);
    ret = PTR_ERR(pcpdrv_data.dev);
    return ret;
  }

  pcpdrv_data.total_devices++; // increment total devices

  printk(KERN_INFO "%s: platform device detected\n", __func__);
  printk(KERN_INFO "%s: device_name: %s\n", __func__, pdev->name);
  printk(KERN_INFO "%s: memory size: %d\n", __func__, pdata->memorySize);
  printk(KERN_INFO "%s: serial number: %s\n", __func__, pdata->serial_number);
  return 0;
}

// get called when a device is removed
static int pcpdrv_remove(struct platform_device *pdev) {
  struct platform_device_data *pdev_data;
  pdev_data = dev_get_drvdata(&pdev->dev); // get platform device data
  device_destroy(pcpdrv_data.class, pdev_data->devt); // destroy device file
  cdev_del(&pdev_data->cdev);                         // delete character device
  pcpdrv_data.total_devices--;                        // decrement total devices

  printk(KERN_INFO "%s: platform device removed\n", __func__);
  return 0;
}

static struct platform_driver pcp_driver = {
    .probe = pcpdrv_probe,
    .remove = pcpdrv_remove,
    .driver =
        {
            .name = "pcp-drv",
            .owner = THIS_MODULE,
        },
};

int __init pcpdrv_init(void) {
  int ret;
  ret = alloc_chrdev_region(&pcpdrv_data.devt, 0, MAX_DEVICES, "pcp-dev");
  if (ret < 0) {
    printk(KERN_ERR "%s: failed to allocate chrdev region\n", __func__);
    return ret;
  }
  pcpdrv_data.class = class_create(THIS_MODULE, "pcp-class");
  if (IS_ERR(pcpdrv_data.class)) {
    printk(KERN_ERR "%s: failed to create class\n", __func__);
    unregister_chrdev_region(pcpdrv_data.devt, MAX_DEVICES);
    ret = PTR_ERR(pcpdrv_data.class);
    return ret;
  }
  ret = platform_driver_register(&pcp_driver);
  if (ret < 0) {
    printk(KERN_ERR "%s: failed to register platform driver\n", __func__);
    return ret;
  }
  printk(KERN_INFO "%s: platform driver registered\n", __func__);
  return 0;
}

void __exit pcpdrv_exit(void) {
  platform_driver_unregister(&pcp_driver);
  class_destroy(pcpdrv_data.class);
  unregister_chrdev_region(pcpdrv_data.devt, MAX_DEVICES);
  printk(KERN_INFO "%s: platform driver unregistered\n", __func__);
}

module_init(pcpdrv_init);
module_exit(pcpdrv_exit);
