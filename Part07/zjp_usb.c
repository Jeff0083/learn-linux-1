#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

static int my_usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk(KERN_INFO "Pen drive (%04X:%04X) plugged\n", id->idVendor,
                                id->idProduct);
	return 0;
}

static void my_usb_disconnect(struct usb_interface *interface)
{
	printk(KERN_INFO "Pen drive removed\n");
}


/*
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
*/

static struct usb_device_id pen_table[] =
{
    { USB_DEVICE(0x0951, 0x1642) },
    {} /* Terminating entry */
};
MODULE_DEVICE_TABLE (usb, pen_table);

static struct usb_driver pen_driver =
{
    .name = "pen_driver",
    .id_table = pen_table,
    .probe = my_usb_probe,
    .disconnect = my_usb_disconnect,
};

static int __init pen_init(void)
{
    return usb_register(&pen_driver);
}

static void __exit pen_exit(void)
{
    usb_deregister(&pen_driver);
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email@sarika-pugs.com>");
MODULE_DESCRIPTION("USB Pen Registration Driver");
