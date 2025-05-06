# Analysis of the сompiled binary with the help of instrumentations

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab6/Egor_Valikov_report_6.md

## Introduction

In this lab, I will study the assembled binaries with instrumentation and study what the instrumentation has brought.

## Analysis of AFL instrumentation in a compiled binary

For this lab work, I took a binary file `json_fuzz_basic` created earlier using afl. Earlier, I described in more detail how the file was created and what problems are associated with it (I have attached a link to the previous report below). Therefore, in this lab I will try to describe what I have not touched on before.

**Link to the previous lab "Fuzzing a JSON-parser with AFL":** [`Egor_Valikov_RE_lab5`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab5/Egor_Valikov_report_5.md)

**Link to the binary file:** [`json_fuzz_basic`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab5/data/json_fuzz_basic)

I have reviewed binary in more detail using the tools from linux and also with the help of ghidra:

```bash
nm json_fuzz_basic | grep afl
readelf -S json_fuzz_basic | grep afl
ghidra
```

![image](https://github.com/user-attachments/assets/111022a8-3493-423f-bccf-40ea0bb9efab)

### The mechanism of AFL-instrumentation

During compilation from `afl-gcc`, some changes occur in the binary. Let's look at them in more detail:

**1. Added instrumentation components**

- **Coverage tracking features:**
  - `__afl_maybe_log` records information about completed paths.
  - `__afl_store` saves coverage data in shared memory.

- **Fork server:**
  - `__afl_forkserver` - speeds up execution by saving state.
  - `__afl_fork_resume` - restores the process state.

- **Data structures:**
  - `__afl_area_ptr` - pointer to a 64KB coverage map.
  - `__afl_prev_loc` - stores information about the previous execution path.
- *p.s. There are many more functions in binary, so I tried to describe the most important of them all.*

**2. Technical changes**

- The file size increased from 36.0 KB (the sum of initial file sizes) to 96.8 KB (`json_fuzz_basic`).
- The number of sections in the file has not changed (the `readelf` command did not show any output, what indicates that there are no new changes).
- The number of characters has increased (which is logical and follows from the first paragraph)





