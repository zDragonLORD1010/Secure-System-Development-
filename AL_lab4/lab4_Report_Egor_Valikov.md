# Lab 4 - Kernel Modules

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/lab4_Report_Egor_Valikov.md

## Introduction

In this lab, I needed to implement the **chardev** `int_stack.ko` core module. This kernel module should implement the `stack<integer>` data structure using **push/pop** operations, as well as support stack size adjustment using `ioctl`. I also implemented a custom `kernel_stack` utility that provides the module's functionality.

## Task 1 - `int_stack` implementation

I have completed all the necessary requirements for this assignment, so let's take a closer look at `file_operations`.

### `open()` and `release()` - initialization and deinitialization of the stack

In fact, nothing happens globally in these two functions, they are called only when the device is **opened** or **closed**.

```c
// Open operation
static int open_op(struct inode *inode, struct file *file) {
    return 0;
}

// Release operation
static int release_op(struct inode *inode, struct file *file) {
    return 0;
}
```

### `read()` - pop operation

For subsequent functions, I have tried to write detailed comments to explain what is going on in them.

```c
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
```

### `write()` - push operation

```c
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
```

### `ioctl(` - configure max stack size

```c
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
```

The full code can be found at the link: [`int_stack.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/data/int_stack.c)

### Creating a Makefile

I wrote a little code so that the `make` command could get the result we need.

```bash
obj-m := int_stack.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
```

Link to the code: [`Makefile`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/data/Makefile)

### `int_stack` health check

The first thing I did was run the make command:

![image](https://github.com/user-attachments/assets/f308cf51-6654-47bc-bedd-5b86cf5a583c)

Then I wrote some tests that test **push/pop** and **ioctl** functions and ran them to test the program's efficiency:

![image](https://github.com/user-attachments/assets/76d19e96-c072-443b-8cc1-e989dbaf2565)

![image](https://github.com/user-attachments/assets/460c3cb7-242b-405e-896c-839037300e6f)

Link to the **push/pop** test: [`test_push_pop.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/data/test_push_pop.c)

Link to the **ioctl** test: [`test_ioctl.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/data/test_ioctl.c)

Everything was working fine, so I started the next task.

## Task 2 - `int_stack` implementation

I implemented the `kernel_stack` utility in the user space, which was a functionality module with the CLI required by the user. In fact, the `kernel_stack` performs the function of an interface for a previously written program, so I will not delve into its functionality. It performs the same operations (**push/pop**, and so on), outputs errors. The only difference is the presence of the **unwind** command, which outputs the entire value from the stack, and the **set-zize** command, which sets the stack size:

```c
void print_usage() {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  kernel_stack set-size <size>\n");
    fprintf(stderr, "  kernel_stack push <value>\n");
    fprintf(stderr, "  kernel_stack pop\n");
    fprintf(stderr, "  kernel_stack unwind\n");
}
```

The full code can be found at the link: [`kernel_stack.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/data/kernel_stack.c)

### Checking the `kernel_stack`

![image](https://github.com/user-attachments/assets/138ebf46-7688-4c04-8b9b-2038858cac2d)

![image](https://github.com/user-attachments/assets/c9b4148c-c378-4781-a452-804e3c8360db)

The only difference from the expected output is the output after the `echo $?` command. The program outputs `222` at `return -ERANGE` in the `push_value` function (if set without the `-` symbol, the program outputs `34`). I think this is not a mistake, because after delving into this topic, I found out that the output `222` will come from `222 = -34` in 8-bit signed. I attached two screenshots from below, on the first one I left the `return -ERANGE` (as required), and on the second one I corrected it to `return ERANGE`:

![image](https://github.com/user-attachments/assets/4264fdaa-60b1-4739-ade5-1d837dd292f2)

![image](https://github.com/user-attachments/assets/9d190bac-abac-4920-8bf9-5e77a07acda8)

## Used resources

The full code of `int_stack` at the link: [`int_stack.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/data/int_stack.c)

Link to the code of `Makefile`: [`Makefile`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/data/Makefile)

The full code of `kernel_stack.c` at the link: [`kernel_stack.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/data/kernel_stack.c)

Link to the **push/pop** test: [`test_push_pop.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/data/test_push_pop.c)

Link to the **ioctl** test: [`test_ioctl.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab4/data/test_ioctl.c)

Folder with all codes: [`data`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/AL_lab4/data)

Folder with all screenshots: [`img`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/AL_lab4/img)
