#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/kdev_t.h>

// Module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sa3ed");
MODULE_DESCRIPTION("A pseudo character driver");

#define DEV_MEM_SIZE 512 // Device memory size
char device_buffer[DEV_MEM_SIZE]; // Device memory

int pcd_open(struct inode *inode, struct file *filp) // Open
{
  printk("%s: Opened\n", __func__);
  return 0;
}

int pcd_release(struct inode *inode, struct file *filp) // Close
{
  printk("%s: Closed\n", __func__);
  return 0;
}

ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos) // Read
{
  printk("%s: Read\n", __func__);
  printk("%s: Count = %ld f_pos = %lld\n", __func__, count, *f_pos); // Print file position
  if ((*f_pos + count) > DEV_MEM_SIZE) // Check if read is beyond device memory
    count = DEV_MEM_SIZE - *f_pos; // Adjust count
  if (copy_to_user(buff, device_buffer + *f_pos, count)) // Copy data from device memory to user buffer
    return -EFAULT;
  *f_pos += count; // Update file position
  printk("%s: number of bytes read = %ld f_pos = %lld\n", __func__, count, *f_pos); // Print file position
  return count; // Return number of bytes read
}

ssize_t pcd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos) // Write
{
  printk("%s: Write\n", __func__);
  printk("%s: Count = %ld f_pos = %lld\n", __func__, count, *f_pos); // Print file position
  if ((*f_pos + count) > DEV_MEM_SIZE) // Check if write is beyond device memory
    count = DEV_MEM_SIZE - *f_pos; // Adjust count
  if (!count){ // Check if count is zero
    printk(KERN_ERR "%s: No space left on device\n", __func__);
    return -ENOMEM;
  }
  if (copy_from_user(device_buffer + *f_pos, buff, count)) // Copy data from user buffer to device memory
    return -EFAULT;
  *f_pos += count; // Update file position
  printk("%s: number of bytes written = %ld f_pos = %lld\n", __func__, count, *f_pos); // Print file position
  return count; // Return number of bytes written
}

loff_t pcd_lseek(struct file *filp, loff_t offset, int whence) // Seek
{
  printk("%s: Seek\n", __func__);
  printk("%s: Offset = %lld \n", __func__, offset); // Print file position
  switch (whence) // Check whence
  {
    case SEEK_SET: // Seek from beginning
      if ((offset < 0) || (offset > DEV_MEM_SIZE)) // Check if offset is beyond device memory
        return -EINVAL;
      filp->f_pos = offset; // Update file position
      break;
    case SEEK_CUR: // Seek from current position
      if (((filp->f_pos + offset) < 0) || ((filp->f_pos + offset) > DEV_MEM_SIZE)) // Check if offset is beyond device memory
        return -EINVAL;
      filp->f_pos += offset; // Update file position
      break;
    case SEEK_END: // Seek from end
      if (((filp->f_pos + offset) < 0) || ((filp->f_pos + offset) > DEV_MEM_SIZE)) // Check if offset is beyond device memory
        return -EINVAL;
      filp->f_pos = DEV_MEM_SIZE + offset; // Update file position
      break;
    default: // Invalid whence
      return -EINVAL;
  }
  printk("%s: New Offset = %lld \n", __func__, offset); // Print file position
  return filp->f_pos; // Return file position
}

dev_t pcd_dev_num; // Global variable for device number
struct cdev pcd_cdev; // Global variable for character device
struct file_operations pcd_fops = { // File operations
  .open = pcd_open,
  .release = pcd_release,
  .read = pcd_read,
  .write = pcd_write,
  .llseek = pcd_lseek,
  .owner = THIS_MODULE
};
struct class *pcd_class;

int __init pcd_driver_init(void) // Constructor
{
  alloc_chrdev_region(&pcd_dev_num, 0, 1, "pcd_dev"); // Dynamically allocate device number
  printk("%s: Device Number = %d Major = %d Minor = %d\n", __func__, pcd_dev_num, MAJOR(pcd_dev_num), MINOR(pcd_dev_num));
  cdev_init(&pcd_cdev, &pcd_fops); // Initialize cdev structure with file operations
  cdev_add(&pcd_cdev, pcd_dev_num, 1); // Add cdev structure to system
  pcd_class = class_create(THIS_MODULE, "pcd_class"); // Create class
  device_create(pcd_class,NULL,pcd_dev_num,NULL,"pcd"); // Create device
  printk("%s: Module Inserted\n", __func__);
  return 0;
}

void __exit pcd_driver_cleanup(void) // Destructor
{
  device_destroy(pcd_class, pcd_dev_num); // Destroy device
  class_destroy(pcd_class); // Destroy class
  cdev_del(&pcd_cdev); // Delete cdev structure from system
  unregister_chrdev_region(pcd_dev_num, 1); // Unregister device number
  printk("%s: Module Removed\n", __func__);
}

module_init(pcd_driver_init); // Register constructor
module_exit(pcd_driver_cleanup); // Register destructor
