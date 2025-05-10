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

- Processes string `"THEPASSWORDISEASYTOCRACK"` (A string hardcoded in the system that will be compared with the response after the loop.).
- `FUN_080484f4` copies the input password into a buffer (`local_100c`).
- `FUN_0804851c` hardcodes string conversion:
  - **Step 1:** Initial XOR (`'T' = 0x54`).
  - **Step 2:** A conversion cycle for each byte:
  - **Step 2.1:** Subtract its index (`iVar4`).
  - **Step 2.2:** XOR with the previous byte.
  - **Step 2.3:** Add the previous byte (with truncation).
  - **Step 2.4:** XOR with the previous byte again.
  - **Step 2.5:** XOR with the 9th byte (index 8).
  - **Step 2.6:** If result is zero, set to 1.
  - **Step 3:** Convert to hexadecimal (Each transformed byte is converted to 2-digit hex).
- Final result is a hex string stored in `local_108c`.

**4. Comparison**

- The program compares the entered string with the encoded one.
- If the passwords match it outputs `"Good work, the password is : ff07031d6fb052490149f44b1d5e94f1592b6bac93c06ca9"`.
- If the passwords don't match it outputs `"Is not the good password !"`.

**5. Program termination**

## Usage example:

While analyzing the **ghidra** code, I discovered a string that is used to compare with the input after its conversion. Therefore, to find out the password, I performed all the same steps as described earlier in paragraph **"Password processing"**. To do this, I wrote a small python code:

```py
def transform_password(hardcoded_str):
    data = bytearray(hardcoded_str.encode())
    
    # Initial XOR on first byte
    if len(data) > 0:
        data[0] ^= 0xAB
    
    # Process subsequent bytes
    for i in range(1, len(data)):
        if data[i] == 0:
            break
        
        # Step 1: Subtract index
        data[i] = (data[i] - i) & 0xFF
        
        # Step 2: XOR with previous byte
        data[i] ^= data[i-1]
        
        # Step 3: Add previous byte
        data[i] = (data[i] + data[i-1]) & 0xFF
        
        # Step 4: XOR with previous byte again
        data[i] ^= data[i-1]
        
        # Step 5: XOR with 9th byte (index 8)
        if len(data) > 8:
            data[i] ^= data[8]
        
        # Step 6: If zero, set to 1
        if data[i] == 0:
            data[i] = 1
    
    # Convert to hex string
    password = ''.join(f'{b:02x}' for b in data if b != 0)
    return password
```

Link to the full code: [`decrypt.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab9/decrypt.py)

![image](https://github.com/user-attachments/assets/d7186ed5-e398-4b31-90e0-d9d10a0477e1)

## Used resourses

Link to the full decrypt code: [`decrypt.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab9/decrypt.py)

Link to the folder with all screenshots: [`img`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab9/img)


