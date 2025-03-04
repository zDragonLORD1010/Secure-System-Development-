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

### Firstly I install `njsscan` and clone the DVNA Repository

I had some problems with the installation, because `njsscan` did not want to be installed through `snap`, `apt`, or `npm`. However, in the end, I was able to install njsscan via `pip` (although the attempts were unsuccessful before that).

![image](https://github.com/user-attachments/assets/d3286cfd-d560-44ea-8d41-560e703c855d)

![image](https://github.com/user-attachments/assets/bc10c5d1-478f-4c2c-a4e1-fe7b9e23fb6b)

![image](https://github.com/user-attachments/assets/5ac06675-7943-4ef6-9cdf-2b64d9aeeef8)

![image](https://github.com/user-attachments/assets/82bc01bb-2910-44ac-92e5-e4e4498afe88)

![image](https://github.com/user-attachments/assets/fcfc2929-ffb9-4ec4-871c-8b1ab2a29f27)

![image](https://github.com/user-attachments/assets/1ed47236-d47b-46b0-9118-023f2d02eda9)

![image](https://github.com/user-attachments/assets/56c107db-9d3e-46ab-b570-6ae9e465445a)

### Next, I scanned the repository using `njsscan`

![image](https://github.com/user-attachments/assets/c94dfa5e-0abb-4fcd-a880-a902ee406f75)

### Here's what I found in my `report.html`

![image](https://github.com/user-attachments/assets/6cd171df-5d51-4658-876c-a79d3c28e08a)

![image](https://github.com/user-attachments/assets/5c8ee26b-1c3c-4f05-8988-9ec1b7f51f53)

![image](https://github.com/user-attachments/assets/a62072f9-b4c5-48ff-b886-c07d004f9365)

### After that, I researched my findings

The full `report.html` can be found at the link: https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab2/task1_njsscan/report.html

#### 1. ERROR Finding

**CWE-611:** Improper Restriction of XML External Entity Reference

![image](https://github.com/user-attachments/assets/6cd171df-5d51-4658-876c-a79d3c28e08a)

The application uses `parseXmlString()` with the `{noent: true}` option to process user-controlled XML data. This makes it possible to resolve foreign entities, which may result in XXE assaults, which give attackers the ability to access any file, carry out SSRF, or carry out DoS attacks.

**Mitigation:**

I recommend disable entity processing by setting `{noent: false}`:

```bash
var products = libxmljs.parseXmlString(req.files.products.data.toString('utf8'), {noent: false, noblanks: true});
```

#### 2. WARNING Finding

**CWE-23:** Relative Path Traversal

![image](https://github.com/user-attachments/assets/5c8ee26b-1c3c-4f05-8988-9ec1b7f51f53)

The `res.render()` function is used with untrusted user input. If an attacker manipulates this input, it may lead to arbitrary file read vulnerabilities.

For example, it might be something like this:

```
?legacy=../../etc/passwd
```

**Mitigation:**

I recommend whitelisting acceptable values for the `req.query.legacy query`, and processing the input data to remove `../` or other malicious characters:

```bash
const whitelist = ['bulkproducts', 'dashboard'];

// If statement checks whitelist and processing the input data

res.render(`app/${app_value}`);
```

#### 3. INFO Finding

**CWE-613:** Insufficient Session Expiration

![image](https://github.com/user-attachments/assets/a62072f9-b4c5-48ff-b886-c07d004f9365)

Because there is no `maxAge` setting in the session configuration, session cookies are always there. This increases the risk of session hijacking.

**Mitigation:**

I recommend setting the `maxAge` value to force session expiration, use `HttpOnly: true` to prevent XSS attacks, and use `secure: true` for HTTPS environments only.

```bash
app.use(session({
  secret: 'keyboard cat',
  resave: true,
  saveUninitialized: false,
  cookie: { 
    secure: true,  // Cookies are sent only over HTTPS protocol
    httpOnly: true, // Prevents JavaScript access to cookies
    maxAge: 3600000 // The session ends after 1 hour
  }
}));
```

## Task 2 - Web Security Mini Labs

### Installing and Setup `BurpSuite`

There were also problems with installing and configuring `BurpSuite`. I was able to install the app, but I couldn't configure it. I changed the proxy settings as needed in different browsers, but all my attempts were unsuccessful. So I decided to try to do the checks where I can manually. (I understand that I won't get a full score for these assignments, but I want to demonstrate some knowledge in this area, hoping to get at least some kind of score)

![image](https://github.com/user-attachments/assets/ef8ad8d0-e87a-44bf-a2ee-065aa80ee329)

![image](https://github.com/user-attachments/assets/9c1c6cc8-9da0-4084-bdcd-bee534038f07)

![image](https://github.com/user-attachments/assets/5d03353f-8d09-41f5-9cbb-4b310b022739)

![image](https://github.com/user-attachments/assets/cae3eeca-3c7d-4d69-a33b-5e8d0b892236)

![image](https://github.com/user-attachments/assets/45b9256e-7680-4530-90c6-57cbef8adb7a)

![image](https://github.com/user-attachments/assets/e741d901-354e-4c78-b5cf-62943084c314)

![image](https://github.com/user-attachments/assets/38839318-cdd4-401e-9a1e-1e332b3e7b83)

### Mini labs

#### Cross Site Scripting

To exploit the XSS vulnerability, I embedded the script in the input line and I successfully managed to run it

![image](https://github.com/user-attachments/assets/38ab4744-bf83-4d55-9b4f-d6412e98da1a)

![image](https://github.com/user-attachments/assets/45e8aad8-6097-4b8f-b875-1ec6c0254b01)

![image](https://github.com/user-attachments/assets/eefc9a86-38a9-456a-8044-1d2796306776)


#### Path Traversal, SQL Injection, Command Injection

Unfortunately, I cannot describe in detail the list of actions that need to be performed in these three points. However, I guess that everything should be turned around by substituting requests and values in requests in BurpSuite.

For example, when using the Command Injection vulnerability, it is worth trying to transfer the vulnerable script after the values 50 and 150 (which initially indicated the size). By analogy, it would be worthwhile to change the value fields for Path Traversal and SQL Injection, but here it's hard for me to say anything more without using BurpSuite.

![image](https://github.com/user-attachments/assets/60076a91-c95f-49e6-a84e-6177edaa7ef2)

![image](https://github.com/user-attachments/assets/42c49364-659e-4f03-99e6-0bcbf92d54b8)

![image](https://github.com/user-attachments/assets/aa6118da-ecdd-486e-a53e-e0fbc9c7ff7b)

#### File Upload

In this assignment, I was trying to upload a file `malicious.html` with a malicious script that I used in Cross Site Scripting, however, I failed to get the proper result. According to the plan, after downloading the malicious file, I had to go to the place where all the downloaded files are stored and select my own (http://127.0.0.1:5000/uploads/malicious.html
), and then the attack worked.

I also tried to download the `shell.jpg` file to use commands through the website. In the `shell.jpg` the following should have been recorded:

```
<?php system($_GET['cmd']); ?>
```

According to the plan, by following links http://127.0.0.1:5000/uploads/shell.jpg?cmd=ls and http://127.0.0.1:5000/uploads/shell.jpg?cmd=cat%20/etc/passwd
, I could execute ls or cat commands, as well as many others by analogy.

![image](https://github.com/user-attachments/assets/609bd7d7-c2f0-488c-91f8-324f3856b776)

![image](https://github.com/user-attachments/assets/227b8087-c36f-45f2-a032-9fe0589de753)

![image](https://github.com/user-attachments/assets/52228dc6-1877-498c-8ffe-f089ea70eb54)

