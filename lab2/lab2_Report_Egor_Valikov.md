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

1. **Severity: LOW**

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

This would cause the system to execute `malicious_input`, as `subprocess.run()` would treat the full command as valid input.

**Mitigation:**

For example, use `shlex.quote()` for input sanitization to ensure that user input is treated as a literal string:

```bash
program = sys.argv[1]
username = shlex.quote(sys.argv[2])
```

2. **Severity: MEDIUM**
