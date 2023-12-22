#include "linux/kern_levels.h"
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sa3ed");
MODULE_DESCRIPTION("A simple pseudo platform driver");

struct platform_driver_data {
  int total_devices;
  dev_t devt;
  struct class *class;
};

// get called when a device is detected
static int pcpdrv_probe(struct platform_device *pdev) {
  printk(KERN_INFO "%s: platform device detected\n", __func__);
  return 0;
}

// get called when a device is removed
static int pcpdrv_remove(struct platform_device *pdev) {
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

int __init pcpdrv_init(void) {
  printk(KERN_INFO "%s: platform driver registered\n", __func__);
  return platform_driver_register(&pcp_driver);
  return 0;
}

void __exit pcpdrv_exit(void) {
  printk(KERN_INFO "%s: platform driver unregistered\n", __func__);
  platform_driver_unregister(&pcp_driver);
}

module_init(pcpdrv_init);
module_exit(pcpdrv_exit);
