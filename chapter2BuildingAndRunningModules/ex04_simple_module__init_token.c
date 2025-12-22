#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

__initdata int count = 5;

__init static int ex04_simple_module_init(void)
{
    int index = 0;

    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);

    for (index = 0; index < count; index++)
    {
        printk(KERN_ALERT "Index = %d\n", index);
    }
    return 0;
}

static void ex04_simple_module_exit(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
}

module_init(ex04_simple_module_init);
module_exit(ex04_simple_module_exit);