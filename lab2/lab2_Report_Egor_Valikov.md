# Lab 2 - Vulnerability Scanning

**Student**: Egor Valikov

**Group**: B22-CBS-01

**Email**: e.valikov@innopolis.university

**Telegram**: @EgorValikov

**Github report**: https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab2/lab2_Report_Egor_Valikov.md

## Task 1 - SAST Tools

I Created a Python virtual environment as needed

![image](https://github.com/user-attachments/assets/ef02551f-3c6c-48bb-8bc2-36684cbb6a10)

## 1.1 `bandit`

### Firstly I install `bandit` and clone the Vulpy Repository

![image](https://github.com/user-attachments/assets/4ae96f48-6c21-4de5-9aad-27d84bd8d478)

![image](https://github.com/user-attachments/assets/48af343c-3527-4000-967e-8b078dc4ec73)

### Next, I scanned the repository using `bandit`

![image](https://github.com/user-attachments/assets/f4898747-8a0c-4c9c-bab0-106939a4e84b)

### Here's what I found in my `report.html`

![image](https://github.com/user-attachments/assets/62564de1-6d2a-43fe-9eca-f0695f508fda)

![image](https://github.com/user-attachments/assets/8b378f8d-97bf-4a1a-b087-66acbccc9f09)

![image](https://github.com/user-attachments/assets/327c30ef-c2dd-4105-aa84-86645cc8fdf0)

### After that, I researched my findings

The full `report.html` can be found at the link: https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab2/task1_bandit/report.html

#### 1. Severity: LOW

**CWE-78:** Improper Neutralization of Special Elements used in an OS Command ('OS Command Injection')

![image](https://github.com/user-attachments/assets/0a171ae2-0773-450e-be9a-fc8bccccca62)

The code tries to brute force a password for a specified username by using the `subprocess` module to execute an external program that is supplied as an input.

![image](https://github.com/user-attachments/assets/bd476780-da8e-4bbf-90b3-e6fec60f2f1b)

In my opinion, the usage of `subprocess.run()` with user-supplied input without adequate sanitization poses potential security problems in this case since it leaves it open to command injection attacks.

If an attacker tried to input something like:

```bash
program = "/bin/sh"
username = "malicious_input"
```

This would cause the system to execute `malicious_input`, and `subprocess.run()` would treat the full command as valid input.

**Mitigation:**

For example, use `shlex.quote()` for input sanitization to ensure that user input is treated as a string:

```bash
program = sys.argv[1]
username = shlex.quote(sys.argv[2])
```

#### 2. Severity: MEDIUM

**CWE-400:** Uncontrolled Resource Consumption

![image](https://github.com/user-attachments/assets/e9466c99-ecc5-404d-b4e0-a90c2723e287)

The `request_without_timeout` refers to the fact that the `requests.get()` call is made without specifying a timeout. 

![image](https://github.com/user-attachments/assets/eb140ac4-4980-4b19-8098-5f3e091c9c85)

This can potentially lead to problems where the request freezes indefinitely if the server is not responding, resulting in a denial of service.

**Mitigation:**

I think the simplest thing to do to prevent this problem is to modify the `requests.get()` call by including the `timeout` parameter in it:

```bash
r = requests.get('http://127.0.1.1:5000/api/post/{}'.format(username), timeout=5)
```

#### 3. Severity: HIGH

**CWE-94:** Improper Control of Generation of Code ('Code Injection')

![image](https://github.com/user-attachments/assets/e48b17ad-4697-42b8-a228-5548917a0a37)

The application is running with `debug=True`, which exposes the Werkzeug debugger.

![image](https://github.com/user-attachments/assets/f9176e52-0d88-4e99-8c87-736bc6f58be7)

An interactive Python shell opens in the browser when the program raises an exception, enabling unauthorized code execution. 

**Mitigation:**

In my opinion, to fix this problem we can simply set the `debug=False` value in the application (or use environment variables to control it):

```bash
app.run(debug=False, host='127.0.1.1', ssl_context=('/tmp/acme.cert', '/tmp/acme.key'))
```

## 1.2 `flawfinder`

### Firstly I install `flawfinder` and clone the DVCP Repository

![image](https://github.com/user-attachments/assets/2d45f3b6-4e7b-419f-9955-4ad78abd1aac)

![image](https://github.com/user-attachments/assets/bbe19590-6f9f-4c29-b2d1-3819608b21ed)

### Next, I scanned the repository using `flawfinder`

![image](https://github.com/user-attachments/assets/36f0d986-b7d8-45a1-9ff4-2711ca7a9f04)

### Here's what I found in my `report.html`

![image](https://github.com/user-attachments/assets/d088749a-0a56-4e4f-80f9-1bd54db5e1c8)

![image](https://github.com/user-attachments/assets/84765250-0626-448e-af41-8c7893a91a05)

![image](https://github.com/user-attachments/assets/dd27ffe6-aa5b-44e4-bef0-eacc8494e73b)

![image](https://github.com/user-attachments/assets/5ef40085-0ccd-431f-adc1-fd2753f20aab)

### After that, I researched my findings

The full `report.html` can be found at the link: https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab2/task1_flawfinder/report.html

#### 1. level 0 vulnerability

**CWE-134:** Use of Externally-Controlled Format String

![image](https://github.com/user-attachments/assets/d088749a-0a56-4e4f-80f9-1bd54db5e1c8)

In theory, if an attacker has access over the format string, they can exploit the `printf` function. But in this scenario I think, there is no actual risk because the format string is a constant.

**Mitigation:**

I think no changes are needed in this case. However, I can recommend using fixed format strings and avoiding transmitting user-controlled data.

#### 2. level 1 vulnerability

**CWE-126:** Buffer Over-read

![image](https://github.com/user-attachments/assets/84765250-0626-448e-af41-8c7893a91a05)

The function `strlen()` calculates the length of a string by looking for a null terminator. A crash or data leak could result from `strlen()` reading more memory than the buffer is allocated if it is not correctly terminated.

**Mitigation:**

I suggest using `strlen()`, which limits the number of characters to read, and also leaving the `shmem_button` so that it always checks that the message is null-terminated.

```bash
size_t bufsize = strnlen(shmem_buf, MAX_BUFFER_SIZE);
```

#### 3. level 2 vulnerability

**CWE-119:** Improper Restriction of Operations within the Bounds of a Memory Buffer
**CWE-120:** Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')

![image](https://github.com/user-attachments/assets/dd27ffe6-aa5b-44e4-bef0-eacc8494e73b)

4 bytes are statically allocated to the `char header[4]` array. If a function writes more than 4 bytes into header, it can cause a buffer overflow, leading to crashes or security vulnerabilities.

**Mitigation:**

First of all, I recommend using safe functions (for example `strncpy()` instead of `strcpy()`) and also increasing the buffer size (maybe use dynamic memory allocation).

#### 4. level 3 or higher vulnerabilities

In the process, I did not find any vulnerabilities above level 2. As I understood it, it was a typo. In another case, this application does not contain such vulnerabilities.

![image](https://github.com/user-attachments/assets/64efeb19-e35e-4d30-b953-f16b34aa0817)

#### 5. false-positive finding

I have created another report (`report1.html`) that should contain all the false-positive findings.

![image](https://github.com/user-attachments/assets/488e9224-0628-482f-abf2-1a9ff650e80d)

The full `report1.html` can be found at the link: https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab2/task1_flawfinder/report1.html

While I was analyzing the `report1.html`, I realized that if the `--falsepositive` flag works correctly, then all vulnerabilities of level 0 and 1, as well as half of the vulnerabilities of level 2, are false-positive. This is the conclusion I made when comparing reports `report.html` (all vulnerabilities) and `report1.html` (only false-positive findings).

In the end, I chose a new false-positive finding to analyze it:

**CWE-362:** Concurrent Execution using Shared Resource with Improper Synchronization ('Race Condition')

![image](https://github.com/user-attachments/assets/925ee23b-36ce-4ede-a24e-193423165517)

As I understand it, the reason why this was flagged as a vulnerability is that `flawfinder` marks the `fopen()` function as potentially dangerous for security. However, this vulnerability can be called a false-positive if the file name is completely controlled by the program (not entered by the user), the file is located in a directory with limited access, and no parallel processes can modify the file between checks and access. In our case, I could not understand exactly why this vulnerability is considered a false-positive, but I believe that the reasons for this are listed above.

## 1.3 `njsscan`


