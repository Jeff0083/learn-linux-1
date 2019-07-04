#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

static dev_t first;

static int __init ofcd_init(void)
{
	int ret;
	printk(KERN_INFO "joeys:ofcd registered \n");
	if((ret = alloc_chrdev_region(&first, 0, 3, "zjp_ofcd")) < 0)
	{
		return ret;
	}
	printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));
	return 0;
	
}

static void __exit ofcd_exit(void)
{
	unregister_chrdev_region(first, 3);
	printk(KERN_INFO "joeys: ofcd unregistered \n");
}

module_init(ofcd_init);
module_exit(ofcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email@sarika-pugs.com>");
MODULE_DESCRIPTION("Our Secend Character Driver");
