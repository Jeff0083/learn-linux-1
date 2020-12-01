#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/delay.h>



static int pid_mem = 1;
int flag = 0;

static void print_mem(struct task_struct *task)
{
        struct mm_struct *mm;
        mm = task->mm;
#if flag==1
        struct vm_area_struct *vma;
        int count = 0;
        printk("\nThis mm_struct has %d vmas.\n", mm->map_count);
        for (vma = mm->mmap ; vma ; vma = vma->vm_next) {
                printk ("\nVma number %d: \n", ++count);
                printk("  Starts at 0x%lx, Ends at 0x%lx, vma flags 0x%x\n",
                          vma->vm_start, vma->vm_end, vma->vm_flags);
        }
        printk("\nPgdp = 0x%lx", &(mm->pgd));
        printk("\nCode  Segment start = 0x%lx, end = 0x%lx \n"
                 "Data  Segment start = 0x%lx, end = 0x%lx\n"
                 "Stack Segment start = 0x%lx\n",
                 mm->start_code, mm->end_code,
                 mm->start_data, mm->end_data,
                 mm->start_stack);
#else
        printk("\nPgdp = 0x%lx", &(mm->pgd));
        printk("\n mm_count = %d, mm_user = %d \n",
                 mm->mm_count, mm->mm_users);

#endif

}

static int mm_exp_load(void){
        struct task_struct *task;
        printk("\nGot the process id to look up as %d, print_flag = %d.\n", pid_mem, flag);
        for_each_process(task) {
                if ( task->pid == pid_mem) {
                        printk("%s[%d]\n", task->comm, task->pid);
			 print_mem(task);
                }
        }
        return 0;
}

static void mm_exp_unload(void)
{
        printk("\nPrint segment information module exiting.\n");
}

module_init(mm_exp_load);
module_exit(mm_exp_unload);
module_param(pid_mem, int, 0);
//module_param(print_flag, int, 1);
