# Lab 2 - Vulnerability Scanning

**Student**: Egor Valikov

**Group**: B22-CBS-01

**Email**: e.valikov@innopolis.university

**Telegram**: @EgorValikov

**Github report**: https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab2/lab2_Report_Egor_Valikov.md

## Task 1 - SAST Tools

I Created a Python virtual environment as needed

![image](https://github.com/user-attachments/assets/ef02551f-3c6c-48bb-8bc2-36684cbb6a10)

## 1.1. `bandit`

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

#### 2. Severity: HIGH

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




