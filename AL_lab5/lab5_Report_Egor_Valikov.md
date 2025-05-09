# Lab 5 - USB

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab5/lab5_Report_Egor_Valikov.md

## Introduction

In this lab, I needed to modify my code from lab 4. It is necessary to add any USB device as an electronic key for `chardev`, so that if the usb device is removed (from lab 4) `chardev` should also be removed from the `/dev` list, and `chardev` should not appear in the system if the electronic key is removed. the key is not inserted in USB port.

## Modification of `int_stack`

I described int_stack in more detail in lab 4, so in this lab I will describe what modifications I have made.

Link to the previous lab: [**Lab 4 - Kernel Modules**](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/lab4_Report_Egor_Valikov.md)

The first step now is to specify your USB device so that the program works correctly:

```c
#define USB_VENDOR_ID 0x1111  // USB VID
#define USB_PRODUCT_ID 0x2222 // USB PID
```

Next, I created a structure for storing information about the USB device, and also added a condition for checking its availability in each operator.

```c
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
```

After that, I added the `usb_probe` function, which initializes the main stack if it has not been initialized before, and also registers the usb device.

```c
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
```

And the final touch was the addition of the `usb_disconnect` function and, for convenience, the creation of the USB driver structure.

```c
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
```

Globally, the code has not changed its functionality, but I have commented and demonstrated the main points. More minor changes can be found in the program code.

The full modified code can be found at the link: [`int_stack.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab5/data/int_stack.c)

## Makefile

Basically nothing has changed in it, but I decided to add a line with automatic compilation of `kernel_stack`.

```bash
obj-m := int_stack.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc kernel_stack.c -o kernel_stack

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -f kernel_stack_usb
```

Link to the code: [`Makefile`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab5/data/Makefile)

## Modification of `kernel_stack.c`

`kernel_stack` has not received any major functional modifications. However, I ran into some problems while writing it, and now, unlike the code that was written earlier, all the functions (**pop**, **push**, and so on) are included in one big main function. There are also some changes due to the fact that the program has become dependent on the USB device, but in my opinion, there is nothing global there.

The full code can be found at the link: [`kernel_stack.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab5/data/kernel_stack.c)

## Test usage example

![image](https://github.com/user-attachments/assets/a254d73f-38f6-4f98-b9cf-98ac8863e726)

## Used resources

The full code of int_stack at the link: [`int_stack.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab5/data/int_stack.c)

Link to the code of Makefile: [`Makefile`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab5/data/Makefile)

The full code of kernel_stack.c at the link: [`kernel_stack.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab5/data/kernel_stack.c)

Folder with all codes: [data](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/AL_lab5/data)

Folder with all screenshots: [img](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/AL_lab5/img)
