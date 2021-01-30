#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/page.h>
#include <linux/printk.h>
#include <linux/syscalls.h>
#include <linux/minix_fs.h>
#include <linux/initrd.h>

unsigned long **real_sys_call_table;
static unsigned long ** get_sct_via_sys_close(void)
{
    unsigned long **entry = (unsigned long **)PAGE_OFFSET;

    for (;(unsigned long)entry < ULONG_MAX; entry += 1) {
        if (entry[__NR_close] == (unsigned long *)sys_close) {
            return entry;  //entry就是sys_call_table的地址
        }
    }
    return NULL;
}


static unsigned long ** get_sct(void)
{
    return get_sct_via_sys_close();
}
 
 
static int __init init_sys_call_memory(void)
{
 
    real_sys_call_table = get_sct();
    printk("PAGE_OFFSET = %lx\n", PAGE_OFFSET);
    printk("sys_call_table = %p\n", real_sys_call_table);
    printk("sys_call_table - PAGE_OFFSET = %lu MiB\n",
             ((unsigned long)real_sys_call_table -
              (unsigned long)PAGE_OFFSET) / 1024 / 1024);
    return 0;
}
 
 
static void __exit exit_sys_call_memory(void)
{
    printk("%s\n", "Farewell the World!");
    return;
}
 
module_init(init_sys_call_memory);
module_exit(exit_sys_call_memory);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("dongshao");

