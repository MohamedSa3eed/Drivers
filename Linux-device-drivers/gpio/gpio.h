#ifndef GPIO_H
#define GPIO_H

struct gpio_dev_private_data {
  char label[20];
  struct gpio_desc *desc;
};

struct gpio_drv_private_data {
  int total_devices;
  struct class *class_gpio;
  struct device **devs;
};

#endif // !GPIO_H
