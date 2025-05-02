# Lab 2 - GDB

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab2/lab2_Report_Egor_Valikov.md

## Introduction

In this lab, we explore reverse engineering and debugging techniques using tools such as `gdb`, `strace`, `ghidra`, and `ldd`. The goal is to analyze the provided application, which requires a `license key` to run. The `license key` is generated using the hardware identifier and stored somewhere in the file system.

## Launching and checking the functions of the `hack_app` application

Initially, I had some problems launching `hack_app` due to the lack of `libssl1.1` in the system. Therefore, I spent some time fixing this error:

![image](https://github.com/user-attachments/assets/0bc87359-9520-46b5-8e98-5b3493cfcc2d)

![image](https://github.com/user-attachments/assets/0abb1596-397f-4c23-a386-143dfdcf9a4d)

![image](https://github.com/user-attachments/assets/c346e30a-b690-4b33-a6c7-d72172a1368f)

### Next, I found out how the `hack_app` works:

1. Displays the message `"Welcome to Lab 2 super secure program!"`.

2. Then it displays a message in which a unique `HWID` is generated based on the computer data and asks you to enter the `license key`.

3. After that, there are several options for the development of events:

  - If the `license key` is entered correctly, the program displays the message `"Now your app is activated! Thanks for purchasing!"`. Moreover, upon further attempts to launch the program, it will display the message `"Your app is licensed to this PC!"`, which indicates that you have successfully entered the correct `license key`.
  - If the `license key` is entered incorrectly, the program will display the message `"Provided key is wrong! App is closing!"`.

4. At the end, the program always outputs the message `"Press Enter to continue..."` and waits for the `Enter` key to be pressed.

## Application analysis using `gidra` and `gdb`

The first thing I did was analyze the `hack_app` through `ghidra`. I looked at the application code, made sure that it worked as it should, and then started searching for how the `license key` is encoded in order to find the correct answer to the task:

![image](https://github.com/user-attachments/assets/7460e369-f797-4f44-9443-e082506b293b)

![image](https://github.com/user-attachments/assets/64fcd6b3-f13e-493b-bd7e-54c1f0a3fad3)

![image](https://github.com/user-attachments/assets/55472fed-8302-4724-9f29-b437ce41d2d3)

![image](https://github.com/user-attachments/assets/ae3dd56d-082c-4d61-a6fd-3e7bad4d9ea8)

I copied all the analysis data from `ghidra` and put it in this file: [`output.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab2/output.txt)

## Creating a `keygen`

After analysis, I tried to write a `keygen` for this application, but I initially failed. So I switched to `patch` and tried to make it. However, while searching for a way to bypass the `license key` verification, I was able to find the correct `license key` that allowed authorization:

![image](https://github.com/user-attachments/assets/f64eaa34-4771-4faf-8ec7-6bbefa3d5a88)

After that, I went back to creating `keygen` and was able to find the answer to how the `license key` is generated correctly:

```py
def generate_license(hwid):
    md5_hash = hashlib.md5(hwid.encode()).hexdigest()
    byte_pairs = [md5_hash[i:i+2] for i in range(0, len(md5_hash), 2)]
    reversed_pairs = byte_pairs[::-1]
    license_key = ''.join(reversed_pairs)
    return license_key
```

The full `keygen` code can be seen at the link: [`keygen.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab2/keygen.py)

### This function works as follows:

1. Calculate the MD5 hash for `HWID`

2. Split into pairs of bytes

3. Reverse the order of the byte pairs.

4. Combine it into the final `license key`

![image](https://github.com/user-attachments/assets/4eccb5c0-4440-4bbd-af88-31a3305f979e)

## Creating a `patch`

After creating `keygen`, I started creating a patch for the `hack_app` application. For a more detailed analysis, I used the `gdb` tool, in which I analyzed the data from the `disassemble` command:

![image](https://github.com/user-attachments/assets/a193cf1f-926b-4e94-80dd-e021a3cf9d15)

In `gdb`, I found the following data that is responsible for checking the `license key`:

```bash
0x000055555555559e <+442>:	jne    0x5555555555a7 <main+451>
0x00005555555555fc <+536>:	jne    0x555555555631 <main+589> 
```

Next, I wrote the following `patch`:

```py
def patch_binary():
    original = "hack_app"
    patched = "hack_app_patched"
    patches = {
        0x159e: "9090",  # First JNE (0x75 0x09 → 0x90 0x90)
        0x15fc: "9090",   # Second JNE (0x75 0x33 → 0x90 0x90)
    }
    with open(original, "rb") as f:
        data = bytearray(f.read())
    for offset, patch in patches.items():
        data[offset:offset+2] = bytes.fromhex(patch)
    with open(patched, "wb") as f:
        f.write(data)
    import os
    os.chmod(patched, 0o755)
    print(f"Created {patched} with license checks disabled")
```

The full `patch` code can be seen at the link: [`patch.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab2/patch.py)

### This function works as follows:

1. Create a patched copy (`hack_app_patched`)

2. Apply fixes (Patch JNE to NOP)

3. Write the corrected binary file

4. Create an executable file

![image](https://github.com/user-attachments/assets/94e09303-7ebb-4fe3-96e3-5a572b0dbcfa)

## Used resources

Folder with all screenshots: [`img`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/AL_lab2/img)

`keygen` code: [`keygen.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab2/keygen.py)

`patch` code: [`patch.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab2/patch.py)

An application with successful authorization that used `keygen`: [`hack_app`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab2/hack_app)

An application with successful authorization that resulted from using `patch`: [`hack_app_patched`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab2/hack_app_patched)

Data from `ghidra` analysis: [`output.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab2/output.txt)
