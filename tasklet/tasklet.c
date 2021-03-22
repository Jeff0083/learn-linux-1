#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>


void work_fcn(unsigned long a)
{
    printk("this is tasklet work function\n");
    while(1);
}

void tasklet_test(void)
{
    struct tasklet_struct task;
    tasklet_init(&task, work_fcn, 0);
    tasklet_schedule(&task);
    //if I don't do the following line, then kernel hang
    tasklet_kill(&task); 
}

static int __init hello_init(void)
{
     tasklet_test();
     return 0;
}


module_init(hello_init);
