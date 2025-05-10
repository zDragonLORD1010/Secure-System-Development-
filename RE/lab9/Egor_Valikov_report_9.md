# Application `8` analysis

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab9/Egor_Valikov_report_9.md

## Introduction

In this lab, I have to figure out the application `8`, explain how it works, and describe in detail what is happening there.

## `8`

First of all, I figured out the file type and analyzed it using ghidra. I have attached basic information about the file below:

![image](https://github.com/user-attachments/assets/298b43ba-915e-4a92-8fb4-7e38f87a620b)

![image](https://github.com/user-attachments/assets/c0f41221-9723-4a8f-a822-9b94ebe1367e)

![image](https://github.com/user-attachments/assets/93a01230-403a-439d-a1d9-4f69f133bfd5)

![image](https://github.com/user-attachments/assets/e8305bc2-67f8-4020-af12-1469db70f146)

![image](https://github.com/user-attachments/assets/60a20ab3-57e8-4015-a617-176cfc31208e)

## Results of the `8` application analysis

It is a 32-bit ELF executable for Linux that functions as a password checker with debugging and input verification mechanisms.

### Description of the application operation

**1. Launching the program**

- The program requires an introductory argument - password.
- If the password is not entered, the program will stop working.
- The program will also stop working in case of a debug.

**2. Password format check**

- Ensures all characters are alphanumeric (using `__ctype_b_loc()`).
- If any character fails, prints `"Bad password !"` and terminates.

**3. Password processing**

- `FUN_080484f4` copies the input password into a buffer (`local_100c`).
- `FUN_0804851c` hardcodes string conversion:
  - Step 1: Initial XOR ().
  - Step 2: A conversion cycle for each byte:
    - Step 2.1: Subtract its index (`iVar4`).
    - Step 2.2: XOR with the previous byte.
    - Step 2.3: Add the previous byte (with truncation).
    - Step 2.4: XOR with the previous byte again.
    - Step 2.5: XOR with the 9th byte (index 8).
    - Step 2.6: If result is zero, set to 1.







