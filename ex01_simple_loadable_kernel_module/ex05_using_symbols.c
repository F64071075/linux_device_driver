#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

int ex05_simple_module_function(void);

static int ex05_simple_module_init(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    ex05_simple_module_function();
    
    return 0;
}

static void ex05_simple_module_exit(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
}

module_init(ex05_simple_module_init);
module_exit(ex05_simple_module_exit);