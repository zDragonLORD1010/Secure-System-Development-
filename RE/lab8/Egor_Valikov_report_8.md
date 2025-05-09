# Fuzzing under libfuzzer

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab8/Egor_Valikov_report_8.md

## Introduction

In this lab, I have to change the sources from previous labs for fuzzing under libfuzzer, assemble, run in different versions, compare.

## Modifying the sources

To work with libfuzzer, I prepared a new code `json_fuzzer.c` and slightly changed the source code so that everything worked correctly.

```c
#include "json_fuzz.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char error[json_error_max];
    json_settings settings = {0};
    
    // Parse the input data
    json_value *value = json_parse_ex(&settings, (const json_char *)data, size, error);
    
    // Free the parsed value if successful
    if (value) {
        json_value_free_ex(&settings, value);
    }
    
    return 0;  // Non-zero return values are reserved for future use.
}
```

Link to the full code `json_fuzzer.c`: [`json_fuzzer.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab8/data/json_fuzzer.c)

## Build the fuzzer with different sanitizers

![image](https://github.com/user-attachments/assets/8d99cb5d-79de-4d63-8ba9-c19157030cb2)

Next, I prepared many different initial tests in the `corpus` folder and created crash report folders for each of the sanitizers.

The folder with the tests: [`corpus`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab8/data/corpus)

ASAN crash reports folder: [`crashes_asan`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab8/data/crashes_asan)

UBSAN crash reports folder: [`crashes_ubsan`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab8/data/crashes_ubsan)

MSAN crash reports folder: [`crashes_msan`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab8/data/crashes_msan)

### Run ASAN fuzzer:

![image](https://github.com/user-attachments/assets/a40d0db2-ee95-40f1-abf5-396af31976f5)

![image](https://github.com/user-attachments/assets/faa481d2-bf5b-4bb3-94c4-b37fd77ddcc5)

### Run UBSAN fuzzer:

![image](https://github.com/user-attachments/assets/4fe26e93-be15-4aca-8fac-4ed31ab2d781)

![image](https://github.com/user-attachments/assets/084884c3-ee7f-43bd-97ac-48b37140bd12)

### Run MSAN fuzzer:

![image](https://github.com/user-attachments/assets/7510fb2e-68f5-4a5e-8d7a-3b8c432dbf82)

![image](https://github.com/user-attachments/assets/6c05ee55-c6ae-4867-abcf-136c5abb7d2c)

### Analysis

All sanitizers detected the same crash with input `"123"` (`Base64: MTIzCg==`). Let's take a closer look at this error.

**Crash Details:**

- **Type:** `Segmentation fault` (SEGV).
- **Location:** `json_value_free_ex()` in `json_fuzz.c`.
- **Trigger:** Input containing just numbers (123).
- **Reason:** Dereference of the null pointer.

Despite the fact that all sanitizers showed one error, everyone described it in their own way.

**Behavior across sanitizers:**

**ASAN:** Detected as memory access violation.
**UBSAN**: Detected as undefined behavior (invalid memory access).
**MSAN:** Also detected the crash but with less detailed output.

## Conclusion

In conclusion, I would like to say that all versions worked well. Everyone identified the same problem. However, there are some differences that I have identified during the analysis.

| Criteria | ASAN | UBSAN | MSAN | 
|--------------------|----------------------------------------|----------------------------------------|----------------------------------------|
| Primary Purpose | Use-after-free, Buffer overflows, Memory leaks, Stack/heap corruption | Integer overflow, Null pointer dereference, Invalid type casts, Misaligned pointers | Reading uninitialized variables, Uninitialized stack/heap memory |
| Performance  | Average in speed, but high in memory cost | The fastest of all | The slowest, requires full program instrumentation |
| Best For | Detecting memory corruption bugs | 	Finding logic errors and unpredictable behavior in code |	Security-critical code where uninitialized reads are dangerous |


## Used resourses

Link to the full code `json_fuzzer.c`: [`json_fuzzer.c`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab8/data/json_fuzzer.c)

The folder with the tests: [`corpus`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab8/data/corpus)

ASAN crash reports folder: [`crashes_asan`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab8/data/crashes_asan)

UBSAN crash reports folder: [`crashes_ubsan`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab8/data/crashes_ubsan)

MSAN crash reports folder: [`crashes_msan`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/RE/lab8/data/crashes_msan)






