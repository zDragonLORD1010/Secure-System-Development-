# `1.exe` analysis

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/final/Egor_Valikov_report_final.md

## Introduction

In this assignment, I have to analyze the application `1.exe` to understand his work and find the flag.

## Main features of the application

`1.exe` — this is a 64-bit Windows console application created using GCC:

- **File Name:** `1.exe`

- **File Type:** PE32 executable (Portable Executable, 32-bit)

- **Target Platform:** Microsoft Windows (GUI application)

- **CPU Architecture:** Intel 80386 (x86)

- **Sections:** Contains 4 sections

- **Linking:** Statically linked

![image](https://github.com/user-attachments/assets/db2d1f83-9f4d-4d28-a7f1-ea418ee6eef1)

![image](https://github.com/user-attachments/assets/2b174985-ca8d-4252-8d59-8124cad7dfff)

## Analysis using `ghidra`

I've analyzed the apps using `ghidra`, so let's take a closer look at it. The application has 3 main functions: `entry`, `FUN_00401160`, and `FUN_00401000`.

### Function `entry`

![image](https://github.com/user-attachments/assets/38b605c6-682a-45da-9a22-f37612f1787f)

```c
undefined4 entry(void)

{
  byte local_88 [128]; // Buffer of 128 bytes
  uint local_8; // Counter for bytes processed
  
  local_8 = FUN_00401160(local_88,&DAT_00402008,0x1c); // Call `FUN_00401160` to decode data from `DAT_00402008`
  local_88[local_8] = 0; // Null-terminate the buffer
  MessageBoxA((HWND)0x0,(LPCSTR)local_88,s_Output_00403 000,0); // Display the decoded message
  return 0;
}
```

**Purpose:**

- The main entry point of the program.
- Decodes data from a hardcoded location `DAT_00402008` and displays it.
- Uses `FUN_00401160` to process the data.
- `local_88` is a 128-byte buffer for decoded message.

### Function `FUN_00401160`

![image](https://github.com/user-attachments/assets/db5e03bb-f9fd-40ec-b5ae-93507b11657a)

```c
uint __cdecl FUN_00401160(byte *param_1,byte *param_2,uint param_3)

{
  byte bVar1; 
  int iVar2;
  uint local_8;
  
  local_8 = 0;
  while( true ) {
    if (param_3 <= local_8) { // Check if all input bytes was processed
      return local_8;
    }
    iVar2 = FUN_00401000(param_1,param_2); // Decode next sequence
    param_2 = param_2 + iVar2; // Move input pointer forward
    bVar1 = *param_1;  // Store decoded byte
    param_1 = param_1 + 1;
    if (bVar1 == 0) break; // Stop on `NULL`
    local_8 = local_8 + 1; // Increment output counter
  }
  return local_8;
}
```

**Purpose:**

- Acts as a loop wrapper for `FUN_00401000`.
- Iterates over the input buffer in UTF-8 encoding (`param_2`).
- Uses `FUN_00401000` to decode each character.
- Writes the result to the `bVar1` until the value is reached: `param_3` (`param_3` prevents buffer overflows) or zero limiter has been detected.
- Returns the number of decoded bytes written to `bVar1`.

### Function `FUN_00401000`

![image](https://github.com/user-attachments/assets/798b092f-9d14-47f3-83bc-98d92f74c05d)

```c
undefined4 __cdecl FUN_00401000(byte *param_1,byte *param _2)

{
  undefined4 local_c; // Number of bytes consumed
  byte local_8; // Decoded byte

  // Check the leading bits to determine the length UTF-8 sequence
  if ((int)(uint)*param_2 >> 3 == 0x1e) { // 4-byte sequence
    local_8 = (byte)((param_2[2] & 0x3f) << 6) | param_2[3] & 0 x3f;
    local_c = 4;
  }
  else if ((int)(uint)*param_2 >> 4 == 0xe) { // 3-byte sequence
    local_8 = (byte)((param_2[1] & 0x3f) << 6) | param_2[2] & 0 x3f;
    local_c = 3;
  }
  else if ((int)(uint)*param_2 >> 5 == 6) { // 2-byte sequence
    local_8 = (byte)((*param_2 & 0x1f) << 6) | param_2[1] & 0x3 f;
    local_c = 2;
  }
  else { // 1-byte
    local_8 = *param_2;
    local_c = 1;
  }
  *param_1 = local_8; // Store the decoded byte
  return local_c; // Return bytes consumed
}
```

**Purpose:**

- Decodes a UTF-8 encoded byte sequence into a single byte.
- Determines the length of the sequence (1–4 bytes) and extracts the correct character.

## Summary

`1.exe` this is a program that, when run, outputs the message `"I never broke the encoding:"`. However, this is not a complete message. Therefore, we will look at how to get the full flag in the next paragraph. In the meantime, I'll summarize a little bit about these three functions in the program:

- `entry` is called by Windows.
- `FUN_00401160` decodes 28 bytes from `DAT_00402008`.
- `FUN_00401000` decodes individual UTF-8 sequences into bytes.

![image](https://github.com/user-attachments/assets/2e46ac81-2fdb-4d85-a2ff-8ef9ce92b4ea)

## Decoding the flag

I have reviewed the data received from `DAT_00402008` and recorded it:

```py
encoded_data = bytes([
0xe0, 0x81, 0x89, 0xc0, 0xa0, 0xc1, 0xae, 0xe0, 0x81, 0xa5, 0xc1, 0xb6,
0xf0, 0x80, 0x81, 0xa5, 0xe0, 0x81, 0xb2, 0xf0, 0x80, 0x80, 0xa0, 0xe0,
0x81, 0xa2, 0x72, 0x6f, 0xc1, 0xab, 0x65, 0xe0, 0x80, 0xa0, 0xe0, 0x81,
0xb4, 0xe0, 0x81, 0xa8, 0xc1, 0xa5, 0x20, 0xc1, 0xa5, 0xe0, 0x81, 0xae,
0x63, 0xc1, 0xaf, 0xe0, 0x81, 0xa4, 0xf0, 0x80, 0x81, 0xa9, 0x6e, 0xc1,
0xa7, 0xc0, 0xba, 0x20, 0x49, 0xf0, 0x80, 0x81, 0x9f, 0xc1, 0xa1, 0xc1,
0x9f, 0xc1, 0x8d, 0xe0, 0x81, 0x9f, 0xc1, 0xb4, 0xf0, 0x80, 0x81, 0x9f,
0xf0, 0x80, 0x81, 0xa8, 0xc1, 0x9f, 0xf0, 0x80, 0x81, 0xa5, 0xe0, 0x81,
0x9f, 0xc1, 0xa5, 0xe0, 0x81, 0x9f, 0xf0, 0x80, 0x81, 0xae, 0xc1, 0x9f,
0xf0, 0x80, 0x81, 0x83, 0xc1, 0x9f, 0xe0, 0x81, 0xaf, 0xe0, 0x81, 0x9f,
0xc1, 0x84, 0x5f, 0xe0, 0x81, 0xa9, 0xf0, 0x80, 0x81, 0x9f, 0x6e, 0xe0,
0x81, 0x9f, 0xe0, 0x81, 0xa7, 0xe0, 0x81, 0x80, 0xf0, 0x80, 0x81, 0xa6,
0xf0, 0x80, 0x81, 0xac, 0xe0, 0x81, 0xa1, 0xc1, 0xb2, 0xc1, 0xa5, 0xf0,
0x80, 0x80, 0xad, 0xf0, 0x80, 0x81, 0xaf, 0x6e, 0xc0, 0xae, 0xf0, 0x80,
0x81, 0xa3, 0x6f, 0xf0, 0x80, 0x81, 0xad, 0x00
])
```

After that, I repeated the decoding function in python and decrypted the flag:

```py
def decode(input_bytes):
    output = []
    i = 0
    while i < len(input_bytes):
        byte = input_bytes[i]
        
        if (byte >> 3) == 0b11110:
            if i + 3 >= len(input_bytes):
                break  # Incomplete sequence
            decoded = ((input_bytes[i + 2] & 0x3F) << 6) | (input_bytes[i + 3] & 0x3F)
            output.append(decoded & 0xFF)  # Truncate to 1 byte
            i += 4
            
        elif (byte >> 4) == 0b1110:
            if i + 2 >= len(input_bytes):
                break
            decoded = ((input_bytes[i + 1] & 0x3F) << 6) | (input_bytes[i + 2] & 0x3F)
            output.append(decoded & 0xFF)
            i += 3
            
        elif (byte >> 5) == 0b110:
            if i + 1 >= len(input_bytes):
                break
            decoded = ((byte & 0x1F) << 6) | (input_bytes[i + 1] & 0x3F)
            output.append(decoded & 0xFF)
            i += 2
            
        else:
            output.append(byte)
            i += 1
            
        if output and output[-1] == 0:
            break
            
    return bytes(output)
```

![image](https://github.com/user-attachments/assets/fd7a101a-9ebd-4690-9fa6-c0b60618742f)

Decoded full flag: `"I never broke the encoding: I_a_M_t_h_e_e_n_C_o_D_i_n_g@flare-on.com"`

The full decryption program can be found at the link: [`decode.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/final/decode.py)

