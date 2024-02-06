#ifndef GPIO_SYSCALLS_H
#define GPIO_SYSCALLS_H

ssize_t direction_show(struct device *dev, struct device_attribute *attr,
                       char *buf);

ssize_t direction_store(struct device *dev, struct device_attribute *attr,
                        const char *buf, size_t count);

ssize_t value_show(struct device *dev, struct device_attribute *attr,
                   char *buf);

ssize_t value_store(struct device *dev, struct device_attribute *attr,
                    const char *buf, size_t count);

ssize_t label_show(struct device *dev, struct device_attribute *attr,
                   char *buf);

#endif // !GPIO_SYSCALLS_H
