#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>

/* module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mohamed Sa3ed");
MODULE_DESCRIPTION("A simple Hello World module");

int param = 0;
module_param(param, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP); // 0644 (permission)
MODULE_PARM_DESC(param, "An integer"); // description

dev_t device_number ;

static int __init hello_init(void) // __init is a macro that marks the init function as "initialization" code and the kernel can free it once the init function finishes for memory optimization
{
  int retval = alloc_chrdev_region(&device_number, 0, 1, "hello"); // alloc_chrdev_region is a function that allocates a range of char device numbers
  if(retval != 0)
  {
    printk("Error allocating device number\n");
    return retval;
  }
  printk("Hello, world! %d\n",param);
  printk("%s: Major number: %d Minor number: %d\n",__FUNCTION__, MAJOR(device_number), MINOR(device_number));
  return retval;
}


static void __exit hello_exit(void) // __exit is a macro that marks the init function as "exit" code and the kernel can free it once the init function finishes for memory optimization
{
  unregister_chrdev_region(device_number, 1); // unregister_chrdev_region is a function that unregisters a range of char device numbers
  printk("Goodbye, world! %d\n",param);
}

module_init(hello_init); // module_init is a macro that tells the kernel which function to run when the module is loaded

module_exit(hello_exit); // module_exit is a macro that tells the kernel which function to run when the module is unloaded


