#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static struct proc_dir_entry* hello_file;

static int hello_show(struct seq_file *m, void *v)
{
	seq_printf(m, "Hello from Niilo, Jarkko and Pyry\n");

	return 0;
}

static int hello_open(struct inode *inode, struct file *file)
{
	return single_open(file, hello_show, NULL);
}

static const struct proc_ops hello_fops = 
{
	.proc_open	= hello_open,
	.proc_read	= seq_read,
	.proc_release	= single_release,
};

static int __init hello_init(void)
{
	printk(KERN_INFO "Module 'read_hello' loaded!\n");

	hello_file = proc_create("read_hello", 0, NULL, &hello_fops);

	if(!hello_file)
	{
		printk(KERN_ALERT "Creating proc entry for read_hello failed.\n");
		return -ENOMEM;
	}

	return 0;
}
static void __exit hello_exit(void)
{
	printk(KERN_INFO "Module 'read_hello' unloaded, bye!\n");

	remove_proc_entry("read_hello", NULL);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL"); //enables usage of this module
MODULE_DESCRIPTION("Sole purpose of this module is to return a hello message when read from /proc");
MODULE_AUTHOR("Pyry Laine");
MODULE_AUTHOR("Jarkko Ahvenniemi");
MODULE_AUTHOR("Niilo Jaakkola");
MODULE_VERSION("1.0");
