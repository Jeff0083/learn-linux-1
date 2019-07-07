#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>

static dev_t first;
struct class *cl;

static int __init ofcd_init(void)
{
	int ret;
	struct device *dev_ret;
	printk(KERN_INFO "joeys:ofcd registered \n");
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
	return 0;
	
}

static void __exit ofcd_exit(void)
{
	class_destroy(cl);
	device_destroy(cl, first);
	unregister_chrdev_region(first, 3);
	printk(KERN_INFO "joeys: ofcd unregistered \n");
}

module_init(ofcd_init);
module_exit(ofcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email@sarika-pugs.com>");
MODULE_DESCRIPTION("Our Secend Character Driver");
