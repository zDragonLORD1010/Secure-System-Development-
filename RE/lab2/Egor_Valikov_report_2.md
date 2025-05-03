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

I had some problems with this task, so I analyzed it without running it. The `ldd` command did not provide any concrete results. However, I was able to look at the file characteristics in more detail through ghidra.

![image](https://github.com/user-attachments/assets/9c8d9636-cc73-454d-9143-92b394f3c98b)

![image](https://github.com/user-attachments/assets/29f4eaaf-6ac6-435d-9aca-2d6bbd062454)

![image](https://github.com/user-attachments/assets/1f55d101-f19c-4462-934d-8240b52d50d5)

![image](https://github.com/user-attachments/assets/57871f96-a595-4824-b891-975aa9ed8bbb)

### Results of the `task_2` application analysis

The `task_2` file is a `relocatable` (relocatable object file), not an executable, so there are no dynamic dependencies in it. This is most likely a Linux kernel object file, which explains the absence of the `main` function (`init_module` is used), as well as the presence of sections `.gnu.linkonce`, `__versions`, `.modinfo`. However, among the interesting findings, I discovered the flag (`license=flag{baee49fd4f7009ff6e932463791f28e6}`) using command `strings`. And also found out that this file is associated with `task_7` (`name=task_7`).

### Key things

- `task_2` is an ELF 64-bit object file for x86-64 architecture.

- The module has a built-in flag: `"flag{baee49fd4f7009ff6e932463791f28e6}"`.

- Module name: `task_7`.

- Has some string data: `"Hello!"` and `"Bye-bye :("`.

### Functionality

- `task_2` implements the basic functionality of outputting.

- `"Hello!"` message is output when the module is loaded.

- `"Bye-bye :("` message is output when the module is unloaded.

- It's using the `printk` function for logging

## `task_3`

I have the same difficulties with this program as with `task_2` because they are the same file types. So I took the same steps as in the case of `task_2`.

![image](https://github.com/user-attachments/assets/9bba2fc3-fd72-4e9e-8478-6ae1da9320a8)

![image](https://github.com/user-attachments/assets/d4ad8773-5aa1-4ef1-91e4-7ccb0d01cbf1)

![image](https://github.com/user-attachments/assets/080e73c9-66be-4774-a143-00b9bf42b537)

![image](https://github.com/user-attachments/assets/8a88c23a-0063-40ef-952d-fe7105bc69e3)

### Results of the `task_3` application analysis

The results of my analysis showed the same thing as in the case of `task_2`. However, I found some interesting facts for the `task_3` file. It is associated with `task_8` (`name=task_8`) and the string `"rEdWcNDya..."` it is most likely encrypted data (most likely it is a flag).

### Key things

- `task_3` is an ELF 64-bit object file for x86-64 architecture.

- The file is not stripped.

- `task_3` is part of the Linux kernel module, but in an intermediate stage of compilation.

- `task_3` has initialization (`init_module`), cleanup, and read operations.

- Module name: `task_8`.

### Functionality

**1. `init_module` function:**

- Registers a symbolic device.

- Creates a device class and a device node.

- Handles errors.

**2. `intro_read` function**

- Allocates `0x26` (38) bytes of memory via `vmalloc`.

- Implements XOR decryption:

- Uses two arrays:
  - `crypted` - first XOR key
  - `"rEdWcNDyavDSNOdKOC95iTEP8bioF3IPmAKUXx"` - second XOR key

- The result is copied to the user space.

### How can I get the flag?

I analyzed `task_3` using the `objdump` command and found 2 keys, wrote a little python code and successfully decoded the flag:

![image](https://github.com/user-attachments/assets/e830dfd2-cc5f-4bf5-b072-7a2c94aa2074)

![image](https://github.com/user-attachments/assets/c1f16419-9e06-4041-bb49-26a21cac96ad)

```py
def decrypt_flag():
    if len(crypted) != len(flag):
        print(f"Warning: Length mismatch! crypted: {len(crypted)}, key2: {len(key2)}")
        
    result = ""
    for i in range(min(len(crypted), len(flag))):
        decrypted_char = chr(crypted[i] ^ ord(flag[i]))
        result += decrypted_char
    
    return result
```

Decrypted flag: `"flag{343b1c4a3ea721b2d640fc8700db0f36}"`

Link to the promgram: [`decrypt.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab2/tasks/task_3/decrypt.py)

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

![image](https://github.com/user-attachments/assets/9e07d2fa-5d80-4fc6-a6f3-4210c81bba73)

![image](https://github.com/user-attachments/assets/acd14520-16a9-4eb6-a168-12ca58268c47)

![image](https://github.com/user-attachments/assets/9c0e80ba-3266-4782-ad07-6c08170638a6)

### Results of the `task_5` application analysis

`task_6` is an ELF executable file. This application did not work on my computer due to library errors related to `pyautogui` (moreover, I did not have the required file `task_4.py`) so I analyzed the entry function and related ones in **ghidra**. `task_6` code is specifically designed to download a Python application that has been packaged using `PyInstaller`. It extracts the necessary files to temporary storage, makes environment settings for the Python interpreter, and executes the Python application package.

### Key components and functionality

**1. Entry point (processEntry)**

- Program calls `__libc_start_main` which is a standard initialization function. It sets up the environment and calls the main program function `thunk_FUN_00403e50`.

**2. The main function of the program (`thunk_FUN_00403e50`)**

- This is the main function that handles the logic of the `PyInstaller` loader. 
- Initializes various buffers and variables
- Checks for the presence of the environment variables `_MEIPASS2` and `_PYI_ONEDIR_MODE`
- Tries to open and check the PyInstaller archive
- If the environment variable `_PYI_PROCNAME` exists, it sets the Linux process name using `prctl`
- Controls the extraction of the embedded Python application and its dependencies
- Sets the temporary directory (`_MEIPASS2`) from which the application will be launched
- Controls the `onedir` and `onefile` modes in `PyInstaller`

**3. Initialization function (`FUN_004086c0`)**

- This is a constructor function that runs the initialization code before running the main program (It performs an initialization array `__DT_INIT_ARRAY`).
- **Key functions:**
- Archive Management
- Environment management
- Controls several environment variables:
  - `_MEIPASS2`: Points to the temporary directory where filesare extracted
  - `_PYI_ONEDIR_MODE`: Determines whether the program is running in onedir mode
  - `_PYI_PROCNAME`: Sets the process name in Linux
- Error handling
- Memory management
- Manages the cleaning of temporary resources

## `task_6`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

![image](https://github.com/user-attachments/assets/19850523-705e-47df-9ce7-f6b28347463a)

![image](https://github.com/user-attachments/assets/dd13b9fb-5485-482b-a0db-98b563b2208f)

![image](https://github.com/user-attachments/assets/f3460d66-f31b-4fc6-9a89-330183ccd297)

![image](https://github.com/user-attachments/assets/f4c4680b-a728-471c-b4d4-ea4b6766b4d0)

### Results of the `task_6` application analysis

`task_6` is an ELF executable file. `task_6` is a program for encrypting/decrypting files using a custom algorithm.

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

![image](https://github.com/user-attachments/assets/1bc199c8-88cb-4d11-a240-522aea4d8708)

![image](https://github.com/user-attachments/assets/f4100bd3-2635-4626-a59a-f92606f699e5)

![image](https://github.com/user-attachments/assets/58e74a33-f88b-4111-9652-86221c5041bc)

### Results of the `task_7` application analysis

`task_7` is an ELF executable file. `task_7` is a text encoder program that accepts a text string as an argument.

### Description of the application operation

**1. Start of the program**

- If the program is running correctly, then proceed to the next step.
- If the application is not running correctly, it displays a message `"Usage: ./task_7 TEXT"`.

**2. Memory allocation**

- The program allocates memory for local variables.

**3. Encrypts the `TEXT`**

- It takes each character of the input text and
applies a sequence of operations to it:
  - Adds the character position in the string (`ADD`)
  - Performs `XOR` with the number 14 (`0xE`)
  - Applies a mask via `AND` with the number 31 (`0x1F`)
  - Subtracts (`position + 1`)

**4. Output the result to the console**

- Outputs the result as binary data
- For example:
  - Input:   `"HELLO"`
  - Output: `05   06   FD   FD   18` (in bytes)

**5. Program termination**

## `task_8`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

![image](https://github.com/user-attachments/assets/6227e13d-b668-4958-a9a1-3b5d57ba02bb)

![image](https://github.com/user-attachments/assets/50f34210-4d81-4d32-88dd-52afedd5e3eb)

### Results of the `task_8` application analysis

`task_8` is an ELF executable file. In this program, I discovered an `entry` function and performed a basic analysis based on it, because many other functions are called from the `entry` function, which in turn cause new ones (it's very difficult to analyze everything). Therefore, I think `task_8` may be part of a system-level application or security-related software, given its processor validation. Because it contains the following points:

- CPU verification
- Stack protection (`in_FS_OFFSET` is typically used for stack protection)
- Structured error handling 
- Multiple initialization checks

### Key components and functionality

**1. Collecting information about the processor**

- The code checks the processor information using the CPUID instruction.
- CPUID with a value of leaf 0 allows you to get basic information about the processor (`piVar1 = (int *)cpuid_basic_info(0)`).
- Then checks if the processor is Intel by comparing the vendor ID string (`0x756e6547` (`"Genu"`) / `0x49656e69` (`"ineI"`) / `0x6c65746e` (`"ntel"`))
- If it's an Intel processor, sets `DAT_0054fea9 = 1`

**2. Processor Version Information**\

- Gets CPU version information using CPUID leaf 1 (`puVar2 = (undefined4 *)cpuid_Version_info(1)`).
- Stores the version info in `DAT_0054ff04`.

**3. Dividing the initialization path**

- The code is then split into two different initialization paths based on `DAT_00520f48`.
- if `DAT_00520f48` is `NULL`:
  - Performs some initialization with CPU info.
  - Checks for a value (`0x123`).
- if `DAT_00520f48` is not `NULL`:
  - Calls a function pointer with specific parameters
  - Sets up some memory offsets
 
**4. Sequential invocation of multiple functions**

- Program calls `FUN_0045d1a0()`, `FUN_0045d160()`, ect.
- Most likely, in these functions, the code performs the final configuration of the program.

## Used resoures

Folder with all used resources (screenshots, decryption codes): [tasks](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab2/tasks)
