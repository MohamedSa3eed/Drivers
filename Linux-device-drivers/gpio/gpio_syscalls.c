#include <linux/device.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include "linux/gpio/consumer.h"

#include "gpio.h"

ssize_t direction_show(struct device *dev, struct device_attribute *attr, char *buf){
  struct gpio_dev_private_data *dev_data = dev_get_drvdata(dev);
  char *direction;
  int dir = gpiod_get_direction(dev_data->desc);
  if (dir < 0){
    printk(KERN_ERR "Error getting direction\n");
    return dir;
  }
  direction = (dir == 0) ? "out" : "in";
  return sprintf(buf, "%s\n", direction);
}

ssize_t direction_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count){
  int ret;
  struct gpio_dev_private_data *dev_data = dev_get_drvdata(dev);
  if(sysfs_streq(buf, "in")){
    ret = gpiod_direction_input(dev_data->desc);
    printk(KERN_INFO "Setting as input ret = %d\n", ret);
  }
  else if(sysfs_streq(buf, "out")){
    ret = gpiod_direction_output(dev_data->desc, 0);
    printk(KERN_INFO "Setting as output ret = %d\n", ret);
  }
  else{
    printk(KERN_ERR "Invalid direction\n");
    ret = -EINVAL;
  }
  return ret? ret : count;
}

ssize_t value_show(struct device *dev, struct device_attribute *attr, char *buf){
  struct gpio_dev_private_data *dev_data = dev_get_drvdata(dev);
  int value = gpiod_get_value(dev_data->desc);
  if (value < 0){
    printk(KERN_ERR "Error getting value\n");
    return value;
  }
  return sprintf(buf, "%d\n", value);
}
ssize_t value_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count){
  int ret = 0;
  struct gpio_dev_private_data *dev_data = dev_get_drvdata(dev);
  if(sysfs_streq(buf, "0")){
    gpiod_set_value(dev_data->desc, 0);
  }
  else if(sysfs_streq(buf, "1")){
    gpiod_set_value(dev_data->desc, 1);
  }
  else{
    printk(KERN_ERR "Invalid value\n");
    ret = -EINVAL;
  }
  return ret? ret : count;
}
ssize_t label_show(struct device *dev, struct device_attribute *attr, char *buf){
  struct gpio_dev_private_data *dev_data = dev_get_drvdata(dev);
  return sprintf(buf, "%s\n", dev_data->label);
}
