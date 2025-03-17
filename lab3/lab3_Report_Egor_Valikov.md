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

I analyzed `program1.c` using `valgrind` and got the following output:

**Link to the full report:** [`valgrind_output1.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output1.txt)

![image](program1_img/Screenshot%20From%202025-03-17%2015-00-00.png)

### Explanation of `valgrind` output

I found the following vulnerabilities here (The description is taken from the CWE website: [CWE-122](https://cwe.mitre.org/data/definitions/122), [CWE-401](https://cwe.mitre.org/data/definitions/401)):

**1. CWE-122: Heap-based Buffer Overflow**

- **Description:** A heap overflow condition is a buffer overflow, where the buffer that can be overwritten is allocated in the heap portion of memory, generally meaning that the buffer was allocated using a routine such as `malloc()`.
- In our case, the program writes data outside of the allocated memory, because `malloc(N)` allocates only `N` bytes instead of `N*sizeof(int)`. Therefore, the simplest option I can suggest is to allocate the size using `malloc(N*sizeof(int))`.

**2. CWE-401: Missing Release of Memory after Effective Lifetime**

- **Description:** The product does not sufficiently track and release allocated memory after it has been used, which slowly consumes remaining memory.
- The allocated memory `malloc(N)` is never freed. So we need to use `free(arr)` at the end of `program1()`.

### Program 1 after fix

**Link to the fixed code of firts program:** [`program1.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/program1.c)

![image](program1_img/Screenshot%20From%202025-03-17%2015-07-47.png)

Verifying the output:

![image](program1_img/Screenshot%20From%202025-03-17%2015-04-38.png)

## Program 2 analysis

### Program creation and testing

First of all, I created `program2.c` file, compiled and tested the program for performance. I got the desired output.

![image](program2_img/Screenshot%20From%202025-03-17%2015-14-09.png)

![image](program2_img/Screenshot%20From%202025-03-17%2015-15-18.png)

### `valgrind` analysis

I analyzed `program2.c` using `valgrind` and got the following output:

**Link to the full report:** [`valgrind_output2.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output2.txt)

![image](program2_img/Screenshot%20From%202025-03-17%2015-22-31.png)

### Explanation of `valgrind` output

I found the following vulnerabilities here (The description is taken from the CWE website: [CWE-416](https://cwe.mitre.org/data/definitions/416)):

**1. CWE-416: Use After Free**

- **Description:** The product reuses or references memory after it has been freed. At some point afterward, the memory may be allocated again and saved in another pointer, while the original pointer references a location somewhere within the new allocation. Any operations using the original pointer are no longer valid because the memory "belongs" to the code that operates on the new pointer.
- In our case, the `work()` function is free `arr`, but `program2()` is still trying to access it. Therefore, I suggest moving `free(arr)` to the end of the `program2()` function and checking `arr` at the beginning, just in case.

Also fixed `memset(arr, 0, sizeof(*arr))` to `memset(arr, 0, N * sizeof(*arr))` (I'm not sure if this refers to a vulnerability like CWE-122, so I just fixed it.).

### Program 2 after fix

**Link to the fixed code of firts program:** [`program2.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/program2.c)

![image](program2_img/Screenshot%20From%202025-03-17%2015-21-01.png)

Verifying the output:

![image](program2_img/Screenshot%20From%202025-03-17%2015-19-34.png)

## Program 3 analysis

### Program creation and testing

First of all, I created `program3.c` file, compiled and tested the program for performance. I got the desired output.

![image](program3_img/Screenshot%20From%202025-03-17%2015-27-26.png)

![image](program3_img/Screenshot%20From%202025-03-17%2015-28-32.png)

### `valgrind` analysis

I analyzed `program3.c` using `valgrind` and got the following output:

**Link to the full report:** [`valgrind_output3.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output3.txt)

![image](program3_img/Screenshot%20From%202025-03-17%2015-29-03.png)

### Explanation of `valgrind` output

I found the following vulnerabilities here (The description is taken from the CWE website: [CWE-690](https://cwe.mitre.org/data/definitions/690)):

**1. CWE-690: Unchecked Return Value to NULL Pointer Dereference**

- **Description:** The product does not check for an error after calling a function that can return with a `NULL` pointer if the function fails, which leads to a resultant `NULL` pointer dereference.
- In our case, we need to add a check at the end, because we can get `arr = NULL`.

I also fixed a typo in the `if` condition (`arr = NULL` to `arr == NULL`) and remove `string.h` because I think we don't need this library (to make the code simpler, especially since it did not affect its performance.).

### Program 3 after fix

**Link to the fixed code of firts program:** [`program3.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/program3.c)

![image](program3_img/photo_2025-03-17_19-09-58.jpg)

Verifying the output:

![image](program3_img/Screenshot%20From%202025-03-17%2015-32-44.png)

## Program 4 analysis

### Program creation and testing

First of all, I created `program4.c` file, compiled and tested the program for performance. I got the desired output.

![image](program4_img/Screenshot%20From%202025-03-17%2015-37-18.png)

![image](program4_img/Screenshot%20From%202025-03-17%2015-38-05.png)

### `valgrind` analysis

I analyzed `program4.c` using `valgrind` and got the following output:

**Link to the full report:** [`valgrind_output4.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output4.txt)

![image](program4_img/Screenshot%20From%202025-03-17%2015-38-23.png)

### Explanation of `valgrind` output

I found the following vulnerabilities here (The description is taken from the CWE website: [CWE-562](https://cwe.mitre.org/data/definitions/562)):

**1. CWE-562: Return of Stack Variable Address**

- **Description:** A function returns the address of a stack variable, which will cause unintended program behavior, typically in the form of a crash.
- The message variable is declared as a local array inside the `getString()` function, which means that it is released (becomes invalid) after the `getString()` function returns. Therefore, to fix this, I first allocate memory on heap (`ret = malloc(100 * sizeof(char))`), then copy string (`strcpy(ret, "Hello World!")`), and then return `ret`. In the end, I have free allocated memory (`free(str)`).

### Program 4 after fix

**Link to the fixed code of firts program:** [`program4.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/program4.c)

![image](program4_img/Screenshot%20From%202025-03-17%2015-42-04.png)

Verifying the output:

![image](program4_img/Screenshot%20From%202025-03-17%2015-41-46.png)

## Task 3 - Vulnerable HashMap Library

First of all, I copied `hash.c` and `hash.h` files, compiled and tested the program for performance. I got the desired output.

![image](hash_img/Screenshot%20From%202025-03-17%2015-48-33.png)

### First `valgrind` analysis

I analyzed `hash.c` using `valgrind` and got the following output:

**Link to the full report:** [`valgrind_output_hash.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output_hash.txt)

![image](hash_img/Screenshot%20From%202025-03-17%2015-49-25.png)

### Implement better practices and fixes for `hash.c`

After I compiled the code, I got some errors in the output (screenshot attached earlier) which I started working on. At the same time, I found possible code vulnerabilities and fixed them.

The first thing I did was start working on the `HashIndex()` function. It contained a potential vulnerability [CWE-125: Out-of-bounds Read](https://cwe.mitre.org/data/definitions/125):

- **Description:** A function returns the address of a stack variable, which will cause unintended program behavior, typically in the form of a crash.
- The condition `for (char* c = key; c; c++)` iterates line-by-line incorrectly, so I change the loop to iterate line-by-line correctly:

![image](hash_img/Screenshot%20From%202025-03-17%2015-54-17.png)

I left the `HashInit()` function almost unchanged, and modified the `HashAdd()` function to avoid the possible vulnerability of [CWE-476: NULL Pointer Dereference](https://cwe.mitre.org/data/definitions/476):

- **Description:** The product dereferences a pointer that it expects to be valid but is NULL.
- - To avoid this error, I set a check `(!map || !value)`.

![image](hash_img/Screenshot%20From%202025-03-17%2015-55-51.png)

In the `HashFind()`, `HashDelete()`, `HashDump()` functions, as well as in the `HashAdd()` function, I suspected a possible vulnerability [CWE-476: NULL Pointer Dereference](https://cwe.mitre.org/data/definitions/476) and fixed it in the same way.

![image](hash_img/Screenshot%20From%202025-03-17%2015-56-41.png)

![image](hash_img/Screenshot%20From%202025-03-17%2015-57-35.png)

I also found a potential vulnerability in `HashDump()` function besides [CWE-476: NULL Pointer Dereference](https://cwe.mitre.org/data/definitions/476). [CWE-134: Use of Externally-Controlled String Format](https://cwe.mitre.org/data/definitions/134):

- **Description:** The product uses a function that accepts a format string as an argument, but the format string originates from an external source.
- To fix it, I used `printf("%s\n", val->KeyName)` instead `printf(val->KeyName)`.

![image](hash_img/Screenshot%20From%202025-03-17%2015-58-28.png)

In the `main()` function, I applied best practices and also fixed possible vulnerabilities that I had encountered before. Moreover, I fixed a potential vulnerability [CWE-401: Missing Release of Memory after Effective Lifetime](https://cwe.mitre.org/data/definitions/401):

- **Description:** The product does not sufficiently track and release allocated memory after it has been used, which slowly consumes remaining memory.
- I changed the `main()` function to release all dynamically allocated items.

![image](hash_img/Screenshot%20From%202025-03-17%2016-03-39.png)

![image](hash_img/Screenshot%20From%202025-03-17%2016-07-13.png)

![image](hash_img/Screenshot%20From%202025-03-17%2016-08-15.png)

I commented out one `printf("HashAdd(map, '%s')\n", pv1->KeyName)` and one `HashAdd(map, pv1)` to avoid the following error. `hash.c` programs worked indefinitely if everything remained in place (I thought it was a typo because the same phrase was written twice).

![image](hash_img/Screenshot%20From%202025-03-17%2016-18-44.png)

### Second `valgrind` analysis

I analyzed `hash.c` using `valgrind` and got the following output:

**Link to the full report:** [`valgrind_output_hash_fix1.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output_hash_fix1.txt)

![image](hash_img/Screenshot%20From%202025-03-17%2016-10-32.png)

![image](hash_img/Screenshot%20From%202025-03-17%2016-22-33.png)

### Final fixes for `hash.c`

According to the analysis, the program worked, but it still had some flaws, so I reviewed the hash.c code again and fixed the `HashDelete()` function. I added line `val = NULL` to it, and line `pv1 = NULL` to the `main()` function.

![image](hash_img/Screenshot%20From%202025-03-17%2016-26-58.png)

### hash.c after fixes

**Link to the fixed code of firts program:** [`hash.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/hash.c)

Verifying the output:

![image](hash_img/Screenshot%20From%202025-03-17%2016-28-32.png)

## Used resources

### 1. Fixed programs:

- [`program1.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/program1.c)
- [`program2.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/program2.c)
- [`program3.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/program3.c)
- [`program4.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/program4.c)
- [`hash.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/hash.c)

### 2. `valgrind` output for all programs:

- [`valgrind_output1.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output1.txt)
- [`valgrind_output2.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output2.txt)
- [`valgrind_output3.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output3.txt)
- [`valgrind_output4.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output4.txt)
- [`valgrind_output_hash.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output_hash.txt)
- [`valgrind_output_hash_fix1.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab3/valgrind_output_hash_fix1.txt)

### 3. All screenshots and remaining data

- **Link:** https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/lab3
- Screenshots in `*_img` folders

