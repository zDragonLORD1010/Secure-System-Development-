# Application Analysis

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab4/Egor_Valikov_report_4.md

## Introduction

In this lab, I have to figure out 2 applications, explain how they work and describe in detail what is happening there.

## `ch25.bin`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

![image](https://github.com/user-attachments/assets/de7a82bd-975a-4c73-9c13-6aeff8d3b2e5)

![image](https://github.com/user-attachments/assets/b96ddb3f-5be6-4e43-8513-cf8b467e0c47)

![image](https://github.com/user-attachments/assets/21870c48-47a1-4984-9f21-b767f013817f)

### Results of the `ch25.bin` application analysis

This is a 32-bit ELF file, an executable file for Unix-like systems. This is a simple program that requires you to enter the required password. She compares it with her encoded password and outputs a message if the password fits.

### Description of the application operation

**1. Checking command line arguments**

- If `argc < 2`, then the program prints `"usage : ./ch25.bin password"`.

**2. Initialization of three strings (`std::string`):**

- `local_14` is loaded from data at `DAT_08048dc4` (hard-wired constant).
- `local_18` is loaded from data at `DAT_08048dcc` (another constant).
- `local_1c` remains raw (for result).

**4. Calling the password verification function `plouf`**

– `s1` is a literal loaded from `DAT_08048dcc` (`local_18`).
– `s2` is a literal loaded from `DAT_08048dc4` (`local_14`).
— In the loop, the **i-th** character is taken from the `s1`, the **i-th** character is taken from the `s2`, their `XOR` is calculated, the result is appended to the output line.

**4. Clearing temporary**

- The destructors for `local_18` and `local_14` are called to free up memory.

**5. Comparing the entered password with the received ones**

- If the password is entered correctly, the program outputs:
  - "Bravo, tu peux valider en utilisant ce mot de passe..."
  - "Congratz. You can validate with this password..."
- If the password is entered incorrectly, the program outputs:
  - "Password incorrect."

**6. Program termination**

- The program terminates with code `0` anyway.

### Usage example

To get the password, I looked at variables `DAT_08048dcc` and `DAT_08048dc4`, and then based on `plouf` function, I made my own decoding code:

`DAT_08048dcc`:

```py
input_bytes = [
    0x50, 0xB3, 0x67, 0xAF, 0xA5, 0x0E, 0x77, 0xA3, 
    0x4A, 0xA2, 0x9B, 0x01, 0x7D, 0x89, 0x61, 0xA5,
    0xA5, 0x02, 0x76, 0xB2, 0x70, 0xB8, 0x89, 0x03,
    0x79, 0xB8, 0x71, 0x95, 0x9B, 0x28, 0x74, 0xBF,
    0x61, 0xBE, 0x96, 0x12, 0x47, 0x95, 0x3E, 0xE1,
    0xA5, 0x04, 0x6C, 0xA3, 0x73, 0xAC, 0x89, 0x00
]
```

`DAT_08048dc4`:

```py
xor_mask = [0x18, 0xD6, 0x15, 0xCA, 0xFA, 0x77]
```

`decrypt.py`:

```py
password = ""
for i in range(len(input_bytes) - 1):
    xor_byte = input_bytes[i] ^ xor_mask[i % len(xor_mask)]
    password += chr(xor_byte)
```

![image](https://github.com/user-attachments/assets/6daa6bac-5af0-4b58-a380-a24c5bada084)

The received password: `"Here_you_have_to_understand_a_little_C++_stuffs"`

The full program code can be found at the link: [`decrypt.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab4/tasks/task_1/decrypt_1.py)

## `ch2.bin`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

![image](https://github.com/user-attachments/assets/25cd820e-224a-45b6-af74-8e1a4a697e3c)

![image](https://github.com/user-attachments/assets/172b0001-bbb6-4fc2-af12-47b7a4a69ee7)

### Results of the `ch2.bin` application analysis

This is a 32-bit ELF file, an executable file for Unix-like systems. This is a simple program that requires entering the required `username` and `password`, which are strictly indicated in the code. Upon successful login, we will receive a corresponding message with some flag.

### Description of the application operation

**1. The program starts**

- The program starts and outputs a message:
  - `############################################################`
  - `##        Bienvennue dans ce challenge de cracking        ##`
  - `############################################################`
- After that, the program asks you to enter your `username`:
  - `username:`

**2. Reading `username` and comparing**

- The program reads the `username` and compares it with `"john"` (`strcmp(pcVar1,"john")`).
- If the input is correct, the application prompts you to enter a `password`:
  - The program outputs a message `password`.
- If not correct, the program outputs a message `"Bad username"`.

**3. Reading `password` and comparing**

- The program reads the `password` and compares it with `"the ripper"` (`strcmp(pcVar1,"the ripper")`).
- If the input is correct, the application outputs a message `"Bien joue, vous pouvez valider l'epreuve avec le mot de passe : 987654321 !"`.
- If not correct, the program outputs a message `"Bad password"`.

**4. Program termination**

- The program terminates with code `0` anyway.

### Usage example

Here I have demonstrated all possible output options of the program:

![image](https://github.com/user-attachments/assets/28f7929b-1a7d-4432-ae46-404fcb488ba7)

## Used resoures

Folder with all used resources (screenshots, decryption codes): [tasks](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab4/tasks)
