# `1.exe` analysis

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab3/Egor_Valikov_report_3.md

## Introduction

In this lab, I need to analyze the application `1.exe` and figure out what encryption mechanism is used in it. To analyze the application, I will use tools such as `ghidra`.

## Main features of the application

`1.exe` — this is a 64-bit Windows console application created using GCC:

- **Architecture:** This is a 64-bit application (`x86_64`).

- **Compiler:** Compiled using GCC version 8.3.0.

- **Dependencies:** The application uses standard C libraries (`msvcrt.dll`) and Windows kernel functions (`KERNEL32.dll`).

![image](https://github.com/user-attachments/assets/fbcdb720-163b-4eb5-b59a-edd5f9884e33)

## Analysis using `ghidra`

I opened the app `1.exe` through `ghidra`. In it, I discovered the main `etry` function from which other functions are called. There are many functions in the application (more than 30), so I concentrated on analyzing the most important. As it seems to me, these are the functions `FUN_00401550` and `FUN_004019a3`. Based on them, I will try to determine the encryption mechanism.

### Function `FUN_00401550`

This function performs actions similar to the implementation of an encryption algorithm:

1. Using a large number of bit operations (shifts, `XOR`).

2. The presence of tables of constants (`DAT_00404020`, `DAT_00404300`, `DAT_00404370`, `DAT_00404340`, etc.).

3. The presence of the parameter `param_3`, which can take the value 'd' for decryption.

4. A cyclic structure with several rounds of operations.

![image](https://github.com/user-attachments/assets/13e30c9d-9848-4b08-92d9-c8a3002af96a)

### Function `FUN_004019a3`

It shows that the same data is encrypted and decrypted several times alternately:

1. The algorithm is called 16 times.

2. Encryption ('e') and decryption ('d') modes are used alternately.

3. The same value is used both as data and as a key (`local_18`).

![image](https://github.com/user-attachments/assets/6416c71b-0beb-49ca-ac66-5f6377b26a61)

## Analysis of the encryption algorithm

**1. Initializing variables:**

- A `local_f8` array is created that will contain the subkeys for the rounds.
- The initial values of the variables `local_34`, `local_48`, `local_50`, `local_58` are set to `0`.

**2. Initial Permutation of the input data:**

- `param_1` is permuted using the `DAT_00404020` table.
- The bits are rearranged according to the values in the table (64 operations).
- The result is stored in `local_50`, the lower 32 bits in `local_30`, the higher ones in `local_2c`.

**3. Key processing:**

- `param_2` is permuted using the `DAT_00404300` table.
- The result is divided into two parts: `local_24` and `local_28`.

**4. Generation of subkeys:**

- In a cycle for each of the 16 rounds:
  - Cyclic shifts of key parts (`local_24` and `local_28`) are performed according to the `DAT_00404370` table.
  - A connection is created for the round via permutation using the `DAT_00404340` table.
  - The subkeys are stored in the `local_f8` array.

**5. Main encryption cycle (16 rounds):**

- The right part of the data (`local_30`) is expanded using the `DAT_004040a0` table.
- Depending on the mode ('e' encryption or 'd' decryption), the connection is selected:
  - When **encrypting**, the connection `local_f8[local_1c]` is used.
  - When **decrypting**, the connection `local_f8[0xf - local_1c]` (reverse) is used.
- `XOR` of the extended data is performed with the connection of the round.
- S-blocks (table `DAT_00404100`) are used for data conversion:
  - Data is divided into 8 parts of 6 bits each.
  - Each part is replaced with a 4-bit value from the S-block.
- Rearranging the bits of the received values using the `DAT_004040e0` table.
- `XOR` with the left side (`local_2c`).
- Swap left and right sides for the next round: `local_2c` becomes `local_30` and new `local_38` becomes `local_2c`.

**6. Final Permutation:**

- The combined data (left + right parts) are rearranged according to the `DAT_00404060` table.
- The result is stored in `local_58` and returned by the function.

## Сonclusion

I believe that in the application `1.exe` an encryption algorithm based on **DES** is used, probably with some modifications. The `FUN_00401550` function implements an algorithm structurally and operationally identical to **DES**. The data in `DAT_00404020` and other similar addresses are most likely **permutation tables** and **S-blocks**.
