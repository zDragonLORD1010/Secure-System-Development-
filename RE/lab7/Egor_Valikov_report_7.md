# Instrumentation of an already assembled binary

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab6/Egor_Valikov_report_6.md

## Introduction

In this assignment, I needed to take the same files as in lab 5, assemble them with a regular compiler, and instrument the already assembled binary by any means necessary. Moreover, I needed to compare the difference in performance, the problems in the instrumentation process that had arisen.

Link to lab 5: [`Fuzzing a JSON-parser with AFL`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab5/Egor_Valikov_report_5.md)

## Initial assembly without tools

I built the binary using the following command:

```bash
gcc -I. -o json_fuzz_clean main.c json_fuzz.c -lm
```

![image](https://github.com/user-attachments/assets/92775331-c5bd-4cb4-9c28-791e9224ebf9)

After that, I got a binary, which I will analyze.

Link to the binary: [`json_fuzz_clean`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab7/json_fuzz_clean)

## Attempts at instrumentation and analysis

I had a lot of problems with the instrumentation here, so I will attach the final commands that gave the result, as well as describe my findings.

### AFL QEMU

I start **AFL QEMU** using the command:

```bash
afl-fuzz -Q -i inputs -o outputs/qemu -- ./json_fuzz_clean @@
```

Globally, the errors types have not changed since lab 5, so I will focus on the differences between **AFL QEMU** among all.

### Analysis:

**1. Falling performance:**

- The execution time has increased significantly: now it runs much slower than before (I didn't measure the time, but it seems to me that it started running at best 10 times slower).
- QEMU overhead has almost doubled (emulation of the entire binary).

**2. Inaccurate code coverage:**

- Only the basic blocks are defined, but not the edge coverage.
- An example of a case of false positives:

```c
if (some_condition) {  // It may be skipped by program
   crash();
}
```

**3. Eerrors:**

- Frequent emulation errors (especially for SSE/AVX instructions).
- A lot of errors related to `"[QEMU] Target binary crashed (signal 11)"`.

**4. Limited error detection:**

- Does not detect:
  - Memory leaks.
  - Stack overflow.
  - Use after release.
 
### DynamoRIO

I start **DynamoRIO** using the command:

```bash
drrun -c afl-dynamorio.so -- ./json_fuzz_clean @@
```

The situation is the same as at **AFL QEMU**, so I'll describe the main differences.

### Analysis:

**1. Falling performance:**

- The execution time has increased significantly: now it runs much slower (It runs faster than **AFL QEMU**, however, the execution speed is still very slow.).
- Memory consumption +300-400MB (DR + instrumentation)

**2. Partial integration with AFL**

- There is no support:
  - Fork servers (each launch is a new process).
  - Persistent mode.
  - Requires custom scripts to collect coverage.
 
**3. Compatibility issues:**

- Conflicts with:
  - LD_PRELOAD
  - Ptrace-based instrumentation
- Does not work with:

```c
_attribute__((section(".some_code"))) // Custom sections
```

**4. Coating Features:**

- More precisely, **QEMU**, but worse than the native build:
- Skips:

```bash
jmp *%rax // Dynamic transitions
```

## Conclusion

I have drawn some conclusions based on the information received. I was comparing with the original build without instrumentation.

| Problem            | AFL QEMU                | DynamoRIO                         |
|--------------------|  --------------------   |     --------------------          |
| Performance        | 15-25 exec/sec          | 40-60 exec/sec                    |
| Coverage accuracy  | Basic blocks (~50%)     | BB + partial edges (~70%)         |
| Memory Errors      | `Segfault` only         | `Segfault` and `Heap corruptions` |
| Stability          | Frequent crashes (~25%) | Average crashes (~10%)            |
| Integration        | Full (but slow)         | Requires customization            |

