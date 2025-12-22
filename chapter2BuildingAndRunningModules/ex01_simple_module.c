#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static int ex01_simple_module_init(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}

static void ex01_simple_module_exit(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
}

module_init(ex01_simple_module_init);
module_exit(ex01_simple_module_exit);