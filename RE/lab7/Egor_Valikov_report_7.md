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

