#include "linux/compiler_types.h"
#include "linux/kern_levels.h"
#include "linux/printk.h"
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/module.h>
#include <linux/uaccess.h>

// Module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sa3ed");
MODULE_DESCRIPTION("A pseudo character driver for multiple devices");

#define DEV_NUM 3 // Number of devices

#define DEV0_MEM_SIZE 512 // Device1 memory size
#define DEV1_MEM_SIZE 512 // Device2 memory size
#define DEV2_MEM_SIZE 512 // Device3 memory size

char device0_buffer[DEV0_MEM_SIZE]; // Device memory
char device1_buffer[DEV1_MEM_SIZE]; // Device memory
char device2_buffer[DEV2_MEM_SIZE]; // Device memory

struct device_data {         // Device data structure
  int size;                  // Device memory size
  char *buffer;              // Device memory
  const char *serial_number; // Device serial number
  struct cdev cdev;          // Character device
};

struct driver_data {                        // Driver data structure
  int total_devices;                        // Total number of devices
  dev_t pcd_dev_num;                        // Device number
  struct device *pcd_device;                // Device
  struct class *pcd_class;                  // Device class
  struct device_data devices_data[DEV_NUM]; // Device data
};

struct driver_data pcd_driver_data = { // Driver data
    .total_devices = DEV_NUM,
    .devices_data = {
         [0] = {
           .size = DEV1_MEM_SIZE,
           .buffer = device0_buffer,
           .serial_number = "PCD_DEV1"
         },
         [1] = {
           .size = DEV2_MEM_SIZE,
           .buffer = device1_buffer,
           .serial_number = "PCD_DEV2"
         },
         [2] = {
           .size = DEV2_MEM_SIZE,
           .buffer = device2_buffer,
           .serial_number = "PCD_DEV3"
         },
    },
};

int pcd_open(struct inode *inode, struct file *filp) { // Open
  int ret; // Return value
  int minor = MINOR(inode->i_rdev); // Get minor number
  struct device_data *device_data; // Device data
  device_data = container_of(inode->i_cdev, struct device_data, cdev); // Get device data
  if (!device_data) { // Check if device data is null
    printk(KERN_ERR "%s: Can't open file for pcd%d\n", __func__, minor);
    ret = -ENOMEM;
  }
  else {
    filp->private_data = device_data; // Set private data
    printk(KERN_INFO "%s: opened file for pcd%d\n", __func__, minor);
    ret = 0;
  }
  return ret;
}

int pcd_release(struct inode *inode, struct file *filp) { // Close
  printk("%s: Closed file for pcd%d\n", __func__, MINOR(inode->i_rdev)); // Print minor number
  return 0;
}

ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos) { // Read
  ssize_t ret; // Return value
  struct device_data *device_data; // Device data
  printk(KERN_INFO "%s: number of bytes requested to read = %ld f_pos = %lld\n", __func__, count, *f_pos); // Print file position
  device_data = (struct device_data *) filp->private_data; // Get device data 
  if ((*f_pos + count) > device_data->size) // Check if read is beyond device memory
    count = device_data->size - *f_pos; // Adjust count
  if (copy_to_user(buff, device_data->buffer + *f_pos, count)) // Copy data from device memory to user buffer
    ret = -EFAULT;
  *f_pos += count; // Update file position
  ret = count; // Set return value
  printk(KERN_INFO "%s: number of bytes read = %ld f_pos = %lld\n", __func__, count, *f_pos); // Print file position
  return ret; // Return number of bytes read
}

ssize_t pcd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos) { // Write
  ssize_t ret; // Return value
  struct device_data *device_data; // Device data
  printk(KERN_INFO "%s: number of bytes requested to write = %ld f_pos = %lld\n", __func__, count, *f_pos); // Print file position
  device_data = (struct device_data *) filp->private_data; // Get device data 
  if ((*f_pos + count) > device_data->size) // Check if read is beyond device memory
    count = device_data->size - *f_pos; // Adjust count
  if (copy_from_user(device_data->buffer + *f_pos, buff, count)) // Copy data from device memory to user buffer
    ret = -EFAULT;
  *f_pos += count; // Update file position
  ret = count; // Set return value
  printk(KERN_INFO "%s: number of bytes written = %ld f_pos = %lld\n", __func__, count, *f_pos); // Print file position
  return ret; // Return number of bytes written
}

loff_t pcd_lseek(struct file *filp, loff_t offset, int whence) { // Seek
  int size; // Device memory size
  printk("%s: Offset = %lld \n", __func__, offset); // Print file position
  size = ((struct device_data *) filp->private_data)->size; // Get device memory size
  switch (whence) { // Check whence
    case SEEK_SET: // Seek from beginning
      if ((offset < 0) || (offset > size)) // Check if offset is beyond device memory
        return -EINVAL;
      filp->f_pos = offset; // Update file position
      break;
    case SEEK_CUR: // Seek from current position
      if (((filp->f_pos + offset) < 0) || ((filp->f_pos + offset) > size)) // Check if offset is beyond device memory
        return -EINVAL;
      filp->f_pos += offset; // Update file position
      break;
    case SEEK_END: // Seek from end
      if (((filp->f_pos + offset) < 0) || ((filp->f_pos + offset) > size)) // Check if offset is beyond device memory
        return -EINVAL;
      filp->f_pos = size + offset; // Update file position
      break;
    default: // Invalid whence
      return -EINVAL;
  }
  printk("%s: New Offset = %lld \n", __func__, offset); // Print file position
  return filp->f_pos;                               // Return file position
}

struct file_operations pcd_fops = { // File operations
    .open = pcd_open,
    .release = pcd_release,
    .read = pcd_read,
    .write = pcd_write,
    .llseek = pcd_lseek,
    .owner = THIS_MODULE
};

int __init pcd_driver_init(void) { // Constructor
  int i; // Iterator
  int ret; // Return value
  ret = alloc_chrdev_region(&pcd_driver_data.pcd_dev_num, 0, DEV_NUM, "pcd_devices"); // Allocate device number
  if (pcd_driver_data.pcd_dev_num < 0) { // Check if device number allocation failed
    printk(KERN_ERR "%s: Device number allocation failed\n", __func__);
    goto out;
  }
  pcd_driver_data.pcd_class = class_create(THIS_MODULE, "pcd_class"); // Create class
  if (IS_ERR(pcd_driver_data.pcd_class)) { // Check if class creation failed
    printk(KERN_ERR "%s: Class creation failed\n", __func__);
    ret = PTR_ERR(pcd_driver_data.pcd_class);
    goto unreg_chrdev;
  }
  for (i = 0; i < DEV_NUM; i++) { // Loop through devices
    printk(KERN_INFO "%s: Device Number = %d Major = %d Minor = %d\n", __func__,
           pcd_driver_data.pcd_dev_num + i,
           MAJOR(pcd_driver_data.pcd_dev_num + i),
           MINOR(pcd_driver_data.pcd_dev_num + i));
    cdev_init(&pcd_driver_data.devices_data[i].cdev, &pcd_fops);  // Initialize cdev structure with file operations
    ret = cdev_add(&pcd_driver_data.devices_data[i].cdev, pcd_driver_data.pcd_dev_num + i, 1); // Add cdev structure to system
    if (ret < 0) { // Check if cdev structure addition failed
      printk(KERN_ERR "%s: cdev addition failed\n", __func__);
      goto cdev_del;
    }
    pcd_driver_data.pcd_device = device_create(pcd_driver_data.pcd_class, NULL, 
                                               pcd_driver_data.pcd_dev_num + i, NULL, "pcd%d", i); // Create device
    if (IS_ERR(pcd_driver_data.pcd_device)) { // Check if device creation failed
      printk(KERN_ERR "%s: Device creation failed\n", __func__);
      ret = PTR_ERR(pcd_driver_data.pcd_device);
      goto class_del;
    }
  }
  printk(KERN_INFO "%s: Module Inserted\n", __func__);
  return ret;
  cdev_del:
  class_del:
    for (; i >= 0; i--){ // Loop through devices
      device_destroy(pcd_driver_data.pcd_class, pcd_driver_data.pcd_dev_num + i); // Destroy device
      cdev_del(&pcd_driver_data.devices_data[i].cdev); // Delete cdev structure from system
    }
    class_destroy(pcd_driver_data.pcd_class); // Destroy class
  unreg_chrdev:
    unregister_chrdev_region(pcd_driver_data.pcd_dev_num, DEV_NUM); // Unregister device number
  out:
    printk(KERN_ERR "%s: Module Insertion Failed\n", __func__);
  return ret;
}

void __exit pcd_driver_cleanup(void) { // Destructor
  int i; // Iterator
  for (i = DEV_NUM-1; i >= 0; i--){ // Loop through devices
    device_destroy(pcd_driver_data.pcd_class, pcd_driver_data.pcd_dev_num + i); // Destroy device
    cdev_del(&pcd_driver_data.devices_data[i].cdev); // Delete cdev structure from system
  }
  class_destroy(pcd_driver_data.pcd_class); // Destroy class
  unregister_chrdev_region(pcd_driver_data.pcd_dev_num, DEV_NUM); // Unregister device number
  printk(KERN_INFO "%s: Module Removed\n", __func__);
}

module_init(pcd_driver_init);    // Register constructor
module_exit(pcd_driver_cleanup); // Register destructor
