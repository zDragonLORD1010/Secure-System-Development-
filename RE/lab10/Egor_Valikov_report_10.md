# Application `9` analysis

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab10/Egor_Valikov_report_10.md

## Introduction

In this lab, I have to figure out the application `9`, explain how it works, and describe in detail what is happening there.

## `9`

First of all, I figured out the file type and analyzed it using **ghidra**. I have attached basic information about the file below:

![image](https://github.com/user-attachments/assets/2f429a94-50bf-40ce-b2f2-cfb59ca4b0a7)

![image](https://github.com/user-attachments/assets/3b373023-9daa-4ba1-978d-e5c98b94066b)

![image](https://github.com/user-attachments/assets/e6e49a29-6e0f-495a-8dc9-5c51a9b76ae5)

## Results of the `9` application analysis

The program is a 64-bit ELF executable file that accepts the username and serial number as input, and then outputs success or error messages.

### Description of the application operation

**1. Launching the program**

- Function `FUN_00101100` verifies the correctness of the number of arguments (program name, `username`, `serial`).
- Checks the serial number format `%x-%x-%x` (three hexadecimal numbers).
- Calls the verification function `FUN_00101470` with the `username` and parsed `serial`.

**2. Process username**

- Takes the `username` and performs several transformations:
  - Reverses the string.
  - Copies it into a buffer.
  - Reverses it again.
  - Pads to 256 bytes.
- Generates an MD5 hash of the transformed `username`.
- Returns the hash in three 4-byte chunks.

**3. Process serial**

- Parse three hex numbers.
- Apply bit manipulation functions (`FUN_001012b0`):
  - Uses two 256-byte lookup tables.
  - Processes each serial part through bitwise AND operations with table values.
  - Uses population count (number of set bits) on results.
  - Performs XOR between counts and builds new values bit-by-bit.
  - Two full passes over different table sections.

**4. Compare results**

- Compares the processed `username` with the modified `serial`.
- Prints success/failure message.

**5. Program termination**







