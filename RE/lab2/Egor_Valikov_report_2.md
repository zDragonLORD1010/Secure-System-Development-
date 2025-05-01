# Application Analysis

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab2/Egor_Valikov_report_2.md

## Introduction

In this lab, I have to figure out 9 applications, explain how they work and describe in detail what is happening there.

## `task_0`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

![image](https://github.com/user-attachments/assets/687e81bd-d141-4da9-9cce-a0db9eb73d09)

![image](https://github.com/user-attachments/assets/c156367a-3bdb-47a1-9be9-8af226e9ec42)

![image](https://github.com/user-attachments/assets/4ef5739c-2528-4bfc-9c9f-6396b1f97185)

### Results of the `task_0` application analysis

`task_0` is an ELF executable file (64-bit Linux binary), which is a simple flag checking program.

#### Description of the application operation

**1. Start of the program**

- At startup, the binary downloads the standard libraries (`libc`), then calls the main function of the application (you can see the function in more detail above, in the section with the analysis with **ghidra**).

**2. Memory allocation**

- The program allocates 400 bytes for a line with the command `malloc(400)`.

**3. Displays the message `"Hello, enter the flag:"`**

**4. Reads input via `scanf()`**

- Reads the input before the first space or line break.

**5. Compares input with a hard-coded flag with the `strcmp()` command**

- Compares the entered string with `"flag{6057f13c496ecf7fd777ceb9e79ae285}"` (`strcmp()` requires an exact match).

**6. Program output and termination**

- If the flag is correct, the `"WIN"` message is displayed.
- If the flag is incorrect, the `"TRY HARDER"` message is displayed.
- The program terminates with code `0` anyway.

#### Usage example:

![image](https://github.com/user-attachments/assets/5e409f7c-9a9e-4931-a4a0-eab37585a92b)

