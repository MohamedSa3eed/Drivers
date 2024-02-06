#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/gpio.h>

#include "gpio.h"
#include "gpio_syscalls.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mohamed Saeed");
MODULE_DESCRIPTION("GPIO Driver");

static DEVICE_ATTR_RW(direction);
static DEVICE_ATTR_RW(value);
static DEVICE_ATTR_RO(label);

static struct attribute *gpio_attrs[] = {
  &dev_attr_direction.attr,
  &dev_attr_value.attr,
  &dev_attr_label.attr,
  NULL
};

static struct attribute_group gpio_attr_group = {
  .attrs = gpio_attrs,
};

static const struct attribute_group *gpio_attr_groups[] = {
  &gpio_attr_group,
  NULL
};

static struct gpio_drv_private_data drv_data;

int gpio_probe(struct platform_device *pdev) {
  const char *label;
  int ret, i = 0;
  struct device *dev = &pdev->dev;
  // get the device node that this platform device is associated with
  struct device_node *parent = pdev->dev.of_node;
  struct device_node *child = NULL;
  struct gpio_dev_private_data *dev_data;
  drv_data.total_devices = of_get_child_count(parent);
  if(!drv_data.total_devices){
    printk(KERN_ERR "No GPIOs found\n");
    return -ENODEV;
  }
  printk(KERN_INFO "Total GPIOs found: %d\n", drv_data.total_devices);
  drv_data.devs = devm_kzalloc(&pdev->dev, sizeof(struct device *) * drv_data.total_devices, GFP_KERNEL);
  for_each_child_of_node(parent, child) {
    /* allocate memory for the private data */
    dev_data = devm_kzalloc(&pdev->dev, sizeof(*dev_data), GFP_KERNEL);
    if (!dev_data) {
      printk(KERN_ERR "Error allocating memory\n");
      return -ENOMEM;
    }
    /* set the private data */
    if (of_property_read_string(child, "label", &label)) {
      printk(KERN_WARNING "cannot read label property\n");
    } else {
      strcpy(dev_data->label, label);
      printk(KERN_INFO "detected GPIO label: %s\n", dev_data->label);
    }
    /* Acuire the GPIO */
    dev_data->desc = devm_fwnode_get_gpiod_from_child(
        dev, "rpi", &child->fwnode, GPIOD_ASIS, dev_data->label);
    if (IS_ERR(dev_data->desc)) {
      printk(KERN_ERR "Error getting GPIO\n");
      return PTR_ERR(dev_data->desc);
    }
    /* set the GPIO default direction */
    ret = gpiod_direction_output(dev_data->desc, 0);
    if (ret) {
      printk(KERN_ERR "Error setting GPIO direction\n");
      return ret;
    }
    /* create the device files under /sys/class/gpio_drv */
    drv_data.devs[i] = device_create_with_groups(drv_data.class_gpio, dev,
                              0, dev_data, gpio_attr_groups,
                              dev_data->label);
    if (IS_ERR(drv_data.devs[i])) {
      printk(KERN_ERR "Error creating device\n");
      return PTR_ERR(drv_data.devs[i]);
    }
    i++;
    printk(KERN_INFO "detected gpio_dev\n");
  }
  return 0;
}

  int gpio_remove(struct platform_device * pdev) {
    int i;
    for(i =0 ; i< drv_data.total_devices; i++){
      device_unregister(drv_data.devs[i]);
    }
    printk(KERN_INFO "GPIOs removed\n");
    return 0; 
  }

struct of_device_id gpio_of_dev_match[] = {
  [0] = { .compatible = "org,rpi-gpio-sysfs"},
  [1] = {}
};

static struct platform_driver gpio_platform_driver = {
  .probe = gpio_probe,
  .remove = gpio_remove,
  .driver = {
    .name = "gpio_drv",
    .owner = THIS_MODULE,
    .of_match_table = of_match_ptr(gpio_of_dev_match),
  },
};

int __init gpio_init(void){
  drv_data.class_gpio = class_create(THIS_MODULE, "gpio_drv");
  if(IS_ERR(drv_data.class_gpio)){
    printk(KERN_ERR "Error creating class\n");
    return PTR_ERR(drv_data.class_gpio);
  }
  platform_driver_register(&gpio_platform_driver);
  printk(KERN_INFO "%s: Hello, World!\n", __func__);
  return 0;
}

void __exit gpio_exit(void){
  platform_driver_unregister(&gpio_platform_driver);
  class_destroy(drv_data.class_gpio);
  printk(KERN_INFO "%s: Goodbye, World!\n", __func__);
}

module_init(gpio_init);
module_exit(gpio_exit);
