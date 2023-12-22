#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sa3ed");
MODULE_DESCRIPTION("A simple pseudo platform device");

static void pcpdev_release(struct device *dev) {
  printk(KERN_INFO "%s: device %s released\n",__func__, dev_name(dev));
}

struct platform_device pdev = {
    .name = "pcp-drv",
    .id = 1,
    .dev = {
        .platform_data = "This is platform data",
        .release = pcpdev_release,
    },
};

static int __init pcpdev_init(void) {
  int ret;
  ret = platform_device_register(&pdev);
  if (ret) {
    printk(KERN_ERR "%s: failed to load platform device\n",__func__);
    return ret;
  }
  printk(KERN_INFO "%s: platform device loaded\n",__func__);
  return 0;
}

static void __exit pcpdev_exit(void) {
  platform_device_unregister(&pdev);
  printk(KERN_INFO "%s: platform device unloaded\n",__func__);
}

module_init(pcpdev_init);
module_exit(pcpdev_exit);
