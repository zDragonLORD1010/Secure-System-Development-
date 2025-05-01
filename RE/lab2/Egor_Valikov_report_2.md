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

### Description of the application operation

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

### Usage example:

![image](https://github.com/user-attachments/assets/5e409f7c-9a9e-4931-a4a0-eab37585a92b)

## `task_1`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

![image](https://github.com/user-attachments/assets/a9725b40-a6a2-4e92-bb86-5a10494a85a6)

![image](https://github.com/user-attachments/assets/0a9016a9-889f-496c-b428-e755028d3756)

![image](https://github.com/user-attachments/assets/ba8e995a-b90d-4e4e-ae78-f019eab9cdfe)

### Results of the `task_1` application analysis

`task_1` has the same type as `task_0`. `task_1` is a more complicated version of `task_0`, which checks the entered flag character-by-character through a series of nested `strncmp()` checks. Unlike the previous program, where the flag was checked in its entirety, step-by-step verification of each symbol is implemented here.

### Description of the application operation

**1. Start of the program**

- At startup, the binary downloads the standard libraries (`libc`), then calls the main function of the application (you can see the function in more detail above, in the section with the analysis with **ghidra**).

**2. Memory allocation**

- The program allocates memory for local variables on the stack (38 characters + service variables).

**3. Displays the message `"Hello, this task is very similar to the previous one, but has some modifications enter the flag:"`**

**4. Reads input via `scanf()`**

- Reads exactly 38 characters via `scanf()` (you can enter it character by character/groups of characters/entirely).

**5. Compares input with a flag with the `strcmp()` command**

- Sequential verification of each character via `strncmp()`.

**6. Program output and termination**

- Checks all 38 characters to the end.
- If all characters are correct, the `"WIN"` message is displayed.
- If there is an error in at least one character, the `"TRY HARDER"` message is displayed.
- The program terminates with code `0`.

### Usage example:

![image](https://github.com/user-attachments/assets/7a545d63-9965-4955-80b7-362e17b2bd67)

## `task_2`

I had some problems with this task, so I analyzed it without running it. The ldd team did not provide any concrete results. However, I was able to look at the file characteristics in more detail through ghidra.

![image](https://github.com/user-attachments/assets/9c8d9636-cc73-454d-9143-92b394f3c98b)

![image](https://github.com/user-attachments/assets/29f4eaaf-6ac6-435d-9aca-2d6bbd062454)

![image](https://github.com/user-attachments/assets/1f55d101-f19c-4462-934d-8240b52d50d5)

![image](https://github.com/user-attachments/assets/57871f96-a595-4824-b891-975aa9ed8bbb)

### Results of the `task_2` application analysis

The `task_2` file is a `relocatable` (relocatable object file), not an executable, so there are no dynamic dependencies in it. This is most likely a Linux kernel object file, which explains the absence of the `main` function (`init_module` is used), as well as the presence of sections `.gnu.linkonce`, `__versions`, `.modinfo`. However, among the interesting findings, I discovered the flag (`license=flag{baee49fd4f7009ff6e932463791f28e6}`) using command `strings`. And also found out that this file is associated with `task_7` (`name=task_7`).

## `task_3`

I have the same difficulties with this program as with `task_2` because they are the same file types. So I took the same steps as in the case of `task_2`.

![image](https://github.com/user-attachments/assets/9bba2fc3-fd72-4e9e-8478-6ae1da9320a8)

![image](https://github.com/user-attachments/assets/d4ad8773-5aa1-4ef1-91e4-7ccb0d01cbf1)

![image](https://github.com/user-attachments/assets/080e73c9-66be-4774-a143-00b9bf42b537)

![image](https://github.com/user-attachments/assets/8a88c23a-0063-40ef-952d-fe7105bc69e3)

### Results of the `task_2` application analysis

The results of my analysis showed the same thing as in the case of `task_2`. However, I found some interesting facts for the `task_3` file. It is associated with `task_8` (`name=task_8`) and the string `"rEdWcNDya..."` it is most likely encrypted data (most likely it is a flag).

## `task_4`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

![image](https://github.com/user-attachments/assets/3b49217d-eee8-46f9-805d-9d22265a5489)

![image](https://github.com/user-attachments/assets/b68c9d1e-7d07-46ef-bcc2-c8f3c04b2fc6)

![image](https://github.com/user-attachments/assets/c0df8fb9-5a60-46f3-9db8-1c5a83612f7d)

![image](https://github.com/user-attachments/assets/8f9257ac-034b-4fa4-b5a9-eff2293e66f5)

### Results of the `task_4` application analysis

`task_4` is an ELF executable file. `task_4` is a program that asks you to guess random numbers (0 or 1). To do this, it uses a standard `random()` generator. If successful, it displays a flag (only with 100% correct answers). It also contains XOR encryption to protect the flag.

### Description of the application operation

**1. Start of the program**

**2. Memory allocation**

- The program allocates memory for local variables.

**3. Displays the message `"Hello, You have to predict random numbers:"`**

**4. Reads input via `scanf()`**

- The program uses pseudorandom numbers (a time-based `random()` generator `srandom(time(0))`)
- In the main loop, you need to predict 1337 (`0x539`) numbers (0 or 1) to get the flag.
- Reads numbers using `scanf()` (if you enter a letter, the program immediately ends with the message `"Oh noo ..."`)

**5. Calculates the number of correct answers and compares them with the total number of answers**

**6. Program output and termination**

- If all 1337 answers are correct, the program decrypts the flag.
- If there is an error in at least one answer, the `"Oh noo ..."` message is displayed.
- The program terminates with code `0`.

### How else can I get the flag?

There are several options to get the flag:

1. Predict all 1337 numbers. This is not a big problem, because they are a function generated by a specific seed (time-dependent) that does not change.

2. Decrypt the key. I found a function that decrypts the flag (the screenshot is attached from above, during the analysis in hydra). In it, I found the `key=param_1 - 0x52c` (in our case, the `key=1337-1324=13`). After that, I wrote a small program that decrypts the protected flag. I found the encrypted flag itself with the `strings` command.

![image](https://github.com/user-attachments/assets/a48ee7b1-0150-4e6b-9325-820bf2120c02)

![image](https://github.com/user-attachments/assets/75629e9f-66ba-43f3-a67d-1c147683ac34)

Encrypted key: `kaljv44o<kk5k<<:5<89<k:k54k4oi9<n9l<:p`

Decrypted key: `flag{99b1ff8f11781541f7f89f9bd41c4a17}`

Link to the promgram: [`test.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab2/tasks/task_4/test.py)

## `task_5`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

## `task_6`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

![image](https://github.com/user-attachments/assets/19850523-705e-47df-9ce7-f6b28347463a)

![image](https://github.com/user-attachments/assets/dd13b9fb-5485-482b-a0db-98b563b2208f)

![image](https://github.com/user-attachments/assets/f3460d66-f31b-4fc6-9a89-330183ccd297)

![image](https://github.com/user-attachments/assets/f4c4680b-a728-471c-b4d4-ea4b6766b4d0)

### Results of the `task_6` application analysis

`task_6` is an ELF executable file. `task_5` is a program for encrypting/decrypting files using a custom algorithm.

### Description of the application operation

**1. Start of the program**

**2. Displays the message `"Hello, it's a custom crypto program Select your option: 1. Encryption 2. Decryption"`**

**3. Reads input via `scanf()`**

- Reads the value (1 or 2)

**4. Encrypting/Decrypting the flag**

- The original and encrypted characters alternate in the output.
- Uses simple bit operations (XOR, addition)
- Requires input files (`flag.txt` and `encrypted_flag.txt`)
- If the value is 1, it reads the data from `flag.txt`, encrypts and writes to `encrypted_flag.txt` (Encryption logic `encrypted_char = (position ^ (char_value - 25 ^ -41) + 31) + 41`)
- If the value is 2, it reads the data from `encrypted_flag.txt`, decrypts and writes to `flag.txt` (Decryption logic `decrypted_char = ((position ^ (enc_char - 41) - 31 ^ -41) + 25)`)

**5. Program termination**

- The program terminates with code `0`.

## `task_7`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

## `task_8`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:
