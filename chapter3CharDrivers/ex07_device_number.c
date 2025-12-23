#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

dev_t dev;
MAJOR(dev);
MINOR(dev);

int register_chrdev_region(dev_t first, unsigned int count, char *name);
int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);
void unregister_chrdev_region(dev_t first, unsigned int count);
