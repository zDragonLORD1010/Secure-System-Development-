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
