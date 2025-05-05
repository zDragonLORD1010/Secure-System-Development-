# Fuzzing a JSON-parser with AFL

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab5/Egor_Valikov_report_5.md

## Introduction

In this lab, I had to assemble a project in different versions using afl, run fuzzing, compare the difference between how it works in different versions, and analyze the crashes.

## Building a project with AFL

I decided to build a project with AFL in two ways:

1. Basic fuzzing (without sanitizers)

2. Fuzzing with AddressSanitizer (ASAN)

### Basic

![image](https://github.com/user-attachments/assets/272f22eb-4b6d-4ce8-8b04-526b3180509d)

- **Goal:** To quickly find obvious crashes and freezes.

- **Advantage:** Maximum execution speed.

- **Disadvantage:** No memory errors detection.

Link to the created file: [`json_fuzz_basic`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab5/data/json_fuzz_basic)

### ASAN

![image](https://github.com/user-attachments/assets/4fb3acc0-706b-4698-b73f-42bb79587a03)

- **Goal:** Search for memory errors (buffer overflows, use-after-free, leaks).

- **Advantage:** Detailed reports on memory corruption.

- **Disadvantage:** Slower than the basic version.

Link to the created file: [`json_fuzz_asan`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab5/data/json_fuzz_asan)

## Launching fuzzing

Before launching, I prepared the `input` and output `folders`:

![image](https://github.com/user-attachments/assets/3c2c74e3-6189-492d-a8c1-9e065cba5d19)

I applied certain settings for each one, and I performed fuzzing until I got 12 crashes (Because it took me a long time).

### General settings

- **Input data:** 4 files (valid/invalid JSON)

- **Timeout:** 5000 ms

- **Mode:** Single Fuzzer

### Basic

![image](https://github.com/user-attachments/assets/0ef48777-48e4-4e9b-82fb-86b2e44b2130)

![image](https://github.com/user-attachments/assets/4269ab4a-0b63-4825-8b24-04768608bf30)

Folder with all crashes: [`basic/crashes`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab5/data/outputs/basic/crashes)

### ASAN

![image](https://github.com/user-attachments/assets/5d1df2d2-334c-446d-82c6-7d07d2f4547c)

![image](https://github.com/user-attachments/assets/8084ea88-a479-4180-a24e-387f08c78e5c)

Folder with all crashes: [`asan/crashes`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab5/data/outputs/asan/crashes)

## Fall analysis

### Basic

![image](https://github.com/user-attachments/assets/e07f7c28-3e43-488b-be81-725414e697db)

I have analyzed crashes `000001` - `000010` and will draw a conclusion based on them. Based on my results, I can identify three main types of failures that occurred during fuzzing:

#### 1. `free(): invalid pointer`

**Crashes:** id:000001, id:000004, id:000005, id:000009, id:000010

**Error description:**

```bash
free(): invalid pointer
Aborted (core dumped)
```

**Reason:**

- The code tries to `free()` a pointer that either:
  - Already released.
  - It is not allocated using `malloc`.
  - The memory is corrupted.

#### 2. `Segmentation fault`

**Crashes:** id:000002, id:000003, id:000006, id:000007, id:000008

**Error description:**

```bash
Segmentation fault (core dumped)
```

**Reasons:**

- Dereference of a `NULL` pointer (for example, `*ptr`, where `ptr = NULL`).

- Heap corruption (for example, **buffer overflow/use after release**).

#### 3. Crash with `object[0].name = ...`

**Crashes:** id:000008

**Error description:**

```bash
object[0].name = 
int:          6
Segmentation fault
```

**Reasons:**

- A distorted JSON object in which the name is empty, but the value exists.

- The parser does not work when accessing the name or value fields.

### ASAN

![image](https://github.com/user-attachments/assets/7712a200-136b-4105-ac69-3d1e553f81c4)

I have analyzed crashes `000001` - `000010` and will draw a conclusion based on them. Based on my results, I can identify three main types of failures that occurred during fuzzing:

#### 1. `NULL` pointer dereferenc

**Crashes:** id:000001, id:000003

**Error description:**

```bash
SEGV on unknown address 0x000000000000 (pc 0x55bfe23a0d90)
Location: json_fuzz.c:212 in json_value_free_ex
```

**Reasons:**

The parser tries to dereference the `NULL` pointer when releasing JSONvalues. This happens in `json_value_free_ex()` when processing malformed strings or objects.

#### 2. Heap buffer overflow

**Crashes:** id:000002, id:000005, id:000007, id:000010

**Error description:**

```bash
heap-buffer-overflow on address 0x503000000068
READ of size 8 at json_fuzz.c:200 in json_value_free_ex
```

**Reasons:**

- The parser reads data from the allocated memory when the object/array values are released. Overflow occurs due to the fact that:
  - The metadata of the object/array is corrupted.
  - The code does not check the `length` fields before accessing the `values[]`.

#### 3. Invalid Free Operations

**Crashes:** id:000004, id:000006, id:000008, id:000009

**Error description:**

```bash
attempting free on address which was not malloc()-ed: 0x50200000002f
Location: json_fuzz.c:215 in json_value_free_ex
```

**Reasons:**

- The parser tries to free up non-heap memory or already free pointers, which is caused by:
  - Pointer arithmetic errors.
  - Double-free scenarios.
  - Corruption of allocation metadata.

## Conclusion

During this lab, I successfully fuzzed the JSON parser using AFL in two build variants: basic and with AddressSanitizer instrumentation. The basic version made it possible to quickly identify critical execution errors, while the ASAN version revealed more complex memory-related problems.

## Used resources

Link to the created **basic** file: [`json_fuzz_basic`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab5/data/json_fuzz_basic)

Link to the created **ASAN** file: [`json_fuzz_asan`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab5/data/json_fuzz_asan)

Folder with all crashes for **basic**: [`basic/crashes`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab5/data/outputs/basic/crashes)

Folder with all crashes for **ASAN**: [`asan/crashes`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab5/data/outputs/asan/crashes)

Folder with screenshots: [`img`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab5/img)

Folder with all used data: [`data`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab5/data)
