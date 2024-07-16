#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/init.h>
#include <linux/sched.h>

static int test_tasks_init(void) {
  struct task_struct *task;
  struct list_head *list;

  list = &task->tasks;

  list_for_each(list, &init_task.tasks) {
	  struct task_struct *task = list_entry(list, struct task_struct, tasks);
      	  printk(KERN_INFO "Parent process: PID=%d, Name=%s\n", task->parent->pid, task->parent->comm);

	  struct task_struct *child;
	  list_for_each_entry(child, &task->children, sibling) {
      		printk(KERN_INFO " ├─ Child process: PID=%d, Name=%s\n", task->pid, task->comm);
	 
	  struct task_struct *sibling = list_entry(child->sibling.next, struct task_struct, sibling);

	  while(&sibling->sibling != &task->children) {
		  printk(KERN_INFO "     ├─ Sibling process: PID=%d, Name=%s\n", sibling->pid, sibling->comm);
		  sibling = list_entry(sibling->sibling.next, struct task_struct, sibling);
	}

    }
  }
  return 0;
}


static void test_tasks_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KK"); 
MODULE_DESCRIPTION("OS mini project"); 

 
module_init(test_tasks_init);
module_exit(test_tasks_exit);