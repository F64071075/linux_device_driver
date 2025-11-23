#include <linux/init.h>
#include <linux/module.h>
#include <asm/current.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple example kernel module");

int print_currect_process_module_init(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    printk(KERN_ALERT "The process is \"%s\" (pid %i)\n", current->comm, current->pid);
    return 0;
}

void print_currect_process_module_exit(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    printk(KERN_ALERT "The process is \"%s\" (pid %i)\n", current->comm, current->pid);
}

module_init(print_currect_process_module_init);
module_exit(print_currect_process_module_exit);