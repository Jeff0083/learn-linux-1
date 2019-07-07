#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

static dev_t first;
struct class *cl;
struct cdev cdev;
static int my_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "joeys:ofcd open \n");
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "joeys:ofcd close\n");
	return 0;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len,
    loff_t *off)
{
	printk(KERN_INFO "joeys:ofcd write\n");
	return len;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "joeys:ofcd read\n");
	return 0;
}
static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
        .open = my_open,
	.release = my_close,
	.write = my_write,
	.read = my_read
};


static int __init ofcd_init(void)
{
	int ret;
	struct device *dev_ret;
	printk(KERN_INFO "joeys:ofcd file operation registered \n");
	if((ret = alloc_chrdev_region(&first, 0, 3, "zjp_ofcd")) < 0)
	{
		return ret;
	}
	
	if((cl = class_create(THIS_MODULE, "chrdev"))< 0)
	{
		unregister_chrdev_region(first, 3);
		return ret;
	}
	
	if((dev_ret = device_create(cl, NULL, first, NULL, "mynull")) < 0)
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

static void __exit ofcd_exit(void)
{
	cdev_del(&cdev);
	device_destroy(cl, first);
	class_destroy(cl);
	unregister_chrdev_region(first, 3);
	printk(KERN_INFO "joeys: ofcd file operation unregistered \n");
}

module_init(ofcd_init);
module_exit(ofcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email@sarika-pugs.com>");
MODULE_DESCRIPTION("Our Secend Character Driver");
