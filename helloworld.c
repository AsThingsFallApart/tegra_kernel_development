#include <linux/module.h>
#include <linux/init.h>

static int __init helloworld_init(void) {
	pr_info("hello_world: Hello world initialization!\n");
	return 0;
}

static void __exit helloworld_exit(void) {
	pr_info("hello_world: Hello world exit!\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Gregory Flynn <gflynn@bestcircuits.com>");
MODULE_DESCRIPTION("Linux module test");
