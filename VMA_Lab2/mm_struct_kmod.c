#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/delay.h>


static int pid_mem = 1;
int flag = 0;

#define cpu_rq(cpu)		(&per_cpu(runqueues, (cpu)))

static void print_mem(struct task_struct *task)
{
        struct mm_struct *mm;
       	struct task_struct *prev, *next;
	unsigned long *switch_count;
	struct rq *rq;
	int cpu;

	cpu = smp_processor_id();
	rq = cpu_rq(cpu);
	prev = rq->curr;
	
	printk("\n the prev= %d, current = %d\n", prev->pid, current->pid);

	mm = task->mm;
        printk("\nPgdp = 0x%lx", &(mm->pgd));
        printk("\n mm_count = %d, mm_user = %d \n",
                 mm->mm_count, mm->mm_users);


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
