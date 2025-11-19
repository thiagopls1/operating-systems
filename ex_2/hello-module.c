#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

MODULE_AUTHOR("Thiago Lins");
MODULE_DESCRIPTION("Hello world driver");
MODULE_LICENSE("MIT");

static int __init custom_init(void) {
  printk(KERN_INFO "Hello World driver loaded.");
  return 0;
}

static void __exit custom_exit(void) {
  printk(KERN_INFO "Goodbye from Hello world driver.");
}

module_init(custom_init);
module_exit(custom_exit);
