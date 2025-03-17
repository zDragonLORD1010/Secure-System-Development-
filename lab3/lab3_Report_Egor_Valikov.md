# Lab 3 - Memory Safety

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/lab3_Report_Egor_Valikov.md

## Task 1/2 Getting started (Program analysis and fix)

I installed needed tools (`gcc` and `valgrind`) without any problems:

![image](program1_img/Screenshot%20From%202025-03-17%2014-57-15.png)

## Program 1 analysis

### Program creation and testing

First of all, I created `program1.c` file, compiled and tested the program for performance. I got the desired output.

![image](program1_img/Screenshot%20From%202025-03-17%2015-01-27.png)

![image](program1_img/Screenshot%20From%202025-03-17%2014-59-02.png)

### `valgrind` analysis

I analyzed program1 using `valgrind` and got the following output:

**Link to the full report:** [`valgrind_output1.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output1.txt)

![image](program1_img/Screenshot%20From%202025-03-17%2015-00-00.png)

### Explanation of `valgrind` output

I found the following vulnerabilities here (The description is taken from the CWE website: [CWE-122](https://cwe.mitre.org/data/definitions/122.html), [CWE-401](https://cwe.mitre.org/data/definitions/401.html)):

**1. CWE-122: Heap-based Buffer Overflow**

- **Description:** A heap overflow condition is a buffer overflow, where the buffer that can be overwritten is allocated in the heap portion of memory, generally meaning that the buffer was allocated using a routine such as `malloc()`.
- In our case, the program writes data outside of the allocated memory, because `malloc(N)` allocates only `N` bytes instead of `N*sizeof(int)`. Therefore, the simplest option I can suggest is to allocate the size using `malloc(N*sizeof(int))`.

**2. CWE-401: Missing Release of Memory after Effective Lifetime**

- **Description:** The product does not sufficiently track and release allocated memory after it has been used, which slowly consumes remaining memory.
- The allocated memory (malloc(N)) is never freed. So we need to use `free(arr)` at the end of `program1()`.

### Program after fix

**Link to the fixed code of firts program:** ['program1.c'](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/program1.c)

![image](program1_img/Screenshot%20From%202025-03-17%2015-07-47.png)

Verifying the output:

![image](program1_img/Screenshot%20From%202025-03-17%2015-04-38.png)



