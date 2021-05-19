#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

static dev_t first;
struct class *cl;
struct cdev cdev;

static DEFINE_MUTEX(zjp_mutex);


static int my_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "joeys:mutex open \n");
	mutex_lock(&zjp_mutex);
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "joeys:mutex close\n");
	mutex_unlock(&zjp_mutex);
	return 0;
}

static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
        .open = my_open,
	.release = my_close,
};


static int __init mutex_zjp_init(void)
{
	int ret;
	struct device *dev_ret;
	printk(KERN_INFO "joeys:mutex file operation registered \n");
	if((ret = alloc_chrdev_region(&first, 0, 3, "zjp_mutex")) < 0)
	{
		return ret;
	}
	
	if((cl = class_create(THIS_MODULE, "chrdev"))< 0)
	{
		unregister_chrdev_region(first, 3);
		return ret;
	}
	
	if((dev_ret = device_create(cl, NULL, first, NULL, "my_mutex")) < 0)
	{
		class_destroy(cl);
		unregister_chrdev_region(first, 3);
		return ret;
	}
	printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));

	cdev_init(&cdev, &my_fops);
	if((ret = cdev_add(&cdev, first, 3)) < 0)
	{
		device_destroy(cl,first);
		class_destroy(cl);
		unregister_chrdev_region(first, 3);
		return ret;
	}
	return 0;
	
}

static void __exit mutex_zjp_exit(void)
{
	cdev_del(&cdev);
	device_destroy(cl, first);
	class_destroy(cl);
	unregister_chrdev_region(first, 3);
	printk(KERN_INFO "joeys: mutex file operation unregistered \n");
}

module_init(mutex_zjp_init);
module_exit(mutex_zjp_exit);

MODULE_LICENSE("GPL");

