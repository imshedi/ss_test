#include <linux/slab.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init my_init(void)
{
	printk("Hello world --> %s\n", __func__);

	return 0;
}

static void __exit my_exit(void)
{
	printk("Exiting...\n");
}

MODULE_AUTHOR("Shreenidhi Shedi");
MODULE_DESCRIPTION("Hello World Module");
MODULE_LICENSE("GPL");

module_init(my_init);
module_exit(my_exit);
