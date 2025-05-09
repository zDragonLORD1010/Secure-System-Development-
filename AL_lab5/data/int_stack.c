#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/errno.h>
#include <linux/usb.h>
#include <linux/kdev_t.h>
#include <linux/device.h>

#define DEVICE_NAME "int_stack"
#define USB_VENDOR_ID 0x1111  // USB VID
#define USB_PRODUCT_ID 0x2222 // USB PID

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Egor Valikov");
MODULE_DESCRIPTION("Lab5 task");

static int major_num;
static struct usb_device *usb_dev = NULL;
static struct class *stack_class;
static dev_t dev_num;

// Stack data structure
struct int_stack {
    int *data;
    int top;
    int max_size;
    struct mutex lock;
};

static struct int_stack stack;

// USB table
static struct usb_id usb_ids[] = {
    { USB_DEVICE(USB_VENDOR_ID, USB_PRODUCT_ID) },
    { }
};
MODULE_DEVICE_TABLE(usb, usb_ids);

// Open operation
static int open_op(struct inode *inode, struct file *file) {

    // Checks for USB key
    if (!usb_dev) {
        printk(KERN_ERR "Access denied: USB key not present\n");
        return -ENODEV;
    }
    return 0;
}

// Release operation
static int release_op(struct inode *inode, struct file *file) {
    return 0;
}

// Read operation
static ssize_t read_op(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    int value;

    // Checks if USB connected
    if (!usb_dev) {
        return -ENODEV;
    }

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

    // Checks if USB connected
    if (!usb_dev)
        return -ENODEV;

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

    // Checks if USB connected
    if (!usb_dev)
        return -ENODEV;
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

//  USB probe
static int usb_probe(struct usb_interface *interface, const struct usb_id *id) {
    usb_dev = interface_to_usbdev(interface);

    // Initialize stack if not initialized yet
    if (!stack.data) {
        stack.data = kmalloc(stack.max_size * sizeof(int), GFP_KERNEL);
        if (!stack.data) {
            usb_dev = NULL;
            return -ENOMEM;
        }
        stack.top = -1;
        mutex_init(&stack.lock);
    }

    // Register device
    major_num = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_num < 0) {
        kfree(stack.data);
        stack.data = NULL;
        usb_dev = NULL;
        return major_num;
    }
    dev_num = MKDEV(major_num, 0);
    device_create(stack_class, NULL, dev_num, NULL, DEVICE_NAME);
    printk(KERN_INFO "USB key inserted, stack device activated\n");
    return 0;
}

// USB disconnect function
static void usb_disconnect(struct usb_interface *interface) {
    device_destroy(stack_class, dev_num);
    unregister_chrdev(major_num, DEVICE_NAME);
    usb_dev = NULL;
    printk(KERN_INFO "USB key removed, stack device deactivated\n");
}

// USB driver structure
static struct usb_driver usb_drv = {
    .name = "int_stack_usb",
    .probe = usb_probe,
    .disconnect = usb_disconnect,
    .id_table = usb_ids,
};

// Initialization
static int __init int_stack_init(void) {
    stack.max_size = 1024;
    stack.data = NULL;

    // Create device class
    stack_class = class_create("int_stack_class");
    if (IS_ERR(stack_class))
        return PTR_ERR(stack_class);

    // Register USB
    int ret = usb_register(&usb_drv);
    if (ret) {
        class_destroy(stack_class);
        return ret;
    }
    printk(KERN_INFO "USB loaded.\n");
    return 0;
}

// Cleanup
static void __exit int_stack_exit(void) {
    usb_deregister(&usb_drv);

    // Checks if USB connected
    if (usb_dev) {
        device_destroy(stack_class, dev_num);
        unregister_chrdev(major_num, DEVICE_NAME);
    }
    if (stack.data)
        kfree(stack.data);
    class_destroy(stack_class);
    printk(KERN_INFO "USB unloaded\n");
}

module_init(int_stack_init);
module_exit(int_stack_exit);
