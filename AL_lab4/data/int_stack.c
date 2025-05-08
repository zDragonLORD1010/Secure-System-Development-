#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/errno.h>

#define DEVICE_NAME "int_stack"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Egor Valikov");
MODULE_DESCRIPTION("Lab4 task");

static int major_num;

// Stack data structure
struct int_stack {
    int *data;
    int top;
    int max_size;
    struct mutex lock;
};

static struct int_stack stack;

// Open operation
static int open_op(struct inode *inode, struct file *file) {
    return 0;
}

// Release operation
static int release_op(struct inode *inode, struct file *file) {
    return 0;
}

// Read operation
static ssize_t read_op(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    int value;

    // Check for invalid argument
    if (len < sizeof(int)) {
        return -EINVAL;
    }
    mutex_lock(&stack.lock);

    // Check for empty stack
    if (stack.top == -1) {
        mutex_unlock(&stack.lock);
        return 0;
    }
    value = stack.data[stack.top--];
    mutex_unlock(&stack.lock);

    // Copy value to user (if bad address - error)
    if (copy_to_user(buf, &value, sizeof(int))) {
        return -EFAULT;
    }
    return sizeof(int);
}

// Write operation
static ssize_t write_op(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    int value;

    // Check for invalid argument
    if (len != sizeof(int)) {
        return -EINVAL;
    }

    // Get value from user
    if (copy_from_user(&value, buf, sizeof(int))) {
        return -EFAULT;
    }
    mutex_lock(&stack.lock);

    // Check for full stack (error if stack is full)
    if (stack.top == stack.max_size - 1) {
        mutex_unlock(&stack.lock);
        return -ERANGE;
    }
    stack.data[++stack.top] = value;
    mutex_unlock(&stack.lock);
    return sizeof(int);
}

// `ioctl` operation
static long ioctl_op(struct file *file, unsigned int cmd, unsigned long arg) {
    int *new_data;
    switch (cmd) {
        case 0:
            // Check for invalid size
            if (arg <= 0) {
                return -EINVAL;
            }
            mutex_lock(&stack.lock);

            // Check for space
            if (arg < stack.top + 1) {
                mutex_unlock(&stack.lock);
                return -ENOSPC;
            }
            new_data = krealloc(stack.data, arg * sizeof(int), GFP_KERNEL);

            // Check for `out of memory` error
            if (!new_data) {
                mutex_unlock(&stack.lock);
                return -ENOMEM;
            }
            stack.data = new_data;
            stack.max_size = arg;
            mutex_unlock(&stack.lock);

            // If success
            return 0;

        // If error (unknown ioctl command)
        default:
            return -ENOTTY;
    }
}

// File operations
static struct file_operations fops = {
    .open = open_op,
    .release = release_op,
    .read = read_op,
    .write = write_op,
    .unlocked_ioctl = ioctl_op,
};

// Initialization
static int __init int_stack_init(void) {
    stack.data = NULL;
    stack.top = -1;
    stack.max_size = 1024;
    stack.data = kmalloc(stack.max_size * sizeof(int), GFP_KERNEL);
    if (!stack.data) {
        return -ENOMEM;
    }
    mutex_init(&stack.lock);
    major_num = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_num < 0) {
        kfree(stack.data);
        return major_num;
    }
    printk(KERN_INFO "Module loaded! Major number: %d\n", major_num);
    return 0;
}

// Cleanup
static void __exit int_stack_exit(void) {
    unregister_chrdev(major_num, DEVICE_NAME);
    kfree(stack.data);
    printk(KERN_INFO "Module unloaded!\n");
}

module_init(int_stack_init);
module_exit(int_stack_exit);
