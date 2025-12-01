#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

// sysmobs to be exported cannot be expressed by static
int ex05_simple_module_function(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}
EXPORT_SYMBOL(ex05_simple_module_function);

static int ex05_simple_module_init(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}

static void ex05_simple_module_exit(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
}

module_init(ex05_simple_module_init);
module_exit(ex05_simple_module_exit);