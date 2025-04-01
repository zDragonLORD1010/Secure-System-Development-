# Lab 4 - Fuzzing

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/lab4_Report_Egor_Valikov.md

## Task 1 - WebApp Fuzzing

### Installation `ffuf` and `secLists` and run DVWA locally with docker

Initially, I successfully installed `ffuf` and `secLists`. There were no difficulties with this.

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_img/install.png)

My next step was to run Run DVWA locally with docker on `127.0.0.1:80:80` (localhost), but there were some problems because this port was already busy. I disabled the previous programs running on this port and successfully launched DVWA.

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_img/docker.png)

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_img/docker_fix.png)

## Fuzz for endpoints using the appropriate wordlists and flags from `secLists`

For all my subsequent commands, I used the template that was attached to the lab:

```bash
ffuf -u http://localhost:80/FUZZ -w <WORDLIST>
```

### Which endpoints/files from `big.txt` were accessible? Which ones gave interesting error codes (not 404).

I used these commands to answer this question. They have the same purpose, the only difference is the additional flag `-fc 404`that adds the 404 error filter.

First command:

```bash
ffuf -u http://localhost:80/FUZZ -w SecLists/Discovery/Web-Content/big.txt
```

Second (modified) command:

```bash
ffuf -u http://localhost:80/FUZZ -w SecLists/Discovery/Web-Content/big.txt -fc 404
```

#### The purpose of the command:

1. Employs `ffuf` for fuzzing the DVWA web application hosted locally.

2. The script iterates through each word in the `big.txt` list, substituting "FUZZ" within the URL for each word.

3. Excludes (`-fc`) any responses that return a 404 status code.

4. Displays only endpoints that can be reached or those that return noteworthy error codes.

#### Executing commands

Running these commands to get reports.

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_img/big.png)

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_img/big_fiter.png)

Full outputs of the first and second commands, respectively:

- The output of the first command without a `-fc` flag: [`big_output.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_output/big_output.txt)

- The output of the second command with a `-fc` flag: [`big_output_filter.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_output/big_output_filter.txt)

#### Output analysis

After analyzing the outputs of the first and second commands, I realized that the `-fc` flag did not affect anything in this case. The difference in the reports was only in the line using the filter (` :: Filter           : Response status: 404`).

#### Accessible files (Endpoints that returned HTTP status 200):

- The `favicon.ico` file

- The `robots.txt` file

#### Interesting error codes (Endpoints that returned HTTP status 403 or 301):

- The endpoints exist, but are redirected to another location (status 301):
  - `config`
  - `docs`
  - `external`

- The endpoints exist, but their number is limited (status 403 or **Forbidden**):
  - `.htaccess`
  - `.htpasswd`
  - `server-status`

### What file extensions from `web-extensions.txt` are available for the index page?

I used this command to answer this question.

Command:

```bash
ffuf -u http://localhost:80/index.FUZZ -w /snap/seclists/current/Discovery/Web-Content/web-extensions.txt
```

#### The purpose of the command:

1. Employs `ffuf` for fuzzing the DVWA web application hosted locally.

2. Tests different file extensions for the index page by appending each extension from the `web-extensions.txt` list to "index".

3. Displays which extensions produce successful responses.

#### Executing command

Running this command to get report.

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_img/web.png)

Full output of the command:

- The output of the command: [`web_output.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_output/web_output.txt)

#### Output analysis

#### Available extensions:

- The `index.php` (status 302)

- The `index.phps` (status 403 or **Forbidden**)

### Which directories from `raft-medium-directories.txt` are accessible? Which ones gave interesting error codes (not 404).

I used these commands to answer this question. They have the same purpose, the only difference is the additional flag `-fc 404`that adds the 404 error filter.

First command:

```bash
ffuf -u http://localhost:80/FUZZ -w /snap/seclists/current/Discovery/Web-Content/raft-medium-directories.txt
```

Second (modified) command:

```bash
ffuf -u http://localhost:80/FUZZ -w /snap/seclists/current/Discovery/Web-Content/raft-medium-directories.txt -fc 404
```

#### The purpose of the command:

1. Employs `ffuf` for fuzzing the DVWA web application hosted locally.

2. Tests directory names from the `raft-medium-directories.txt` list to identify accessible directories or those with interesting responses.

3. Excludes (`-fc`) any responses that return a 404 status code.

4. Displays only endpoints that can be reached or those that return noteworthy error codes.

#### Executing commands

Running these commands to get reports.

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_img/raft.png)

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_img/raft_filter.png)

Full outputs of the first and second commands, respectively:

- The output of the first command without a `-fc` flag: [`raft_output.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_output/raft_output.txt)

- The output of the second command with a `-fc` flag: [`raft_output_filter.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_output/raft_output_filter.txt)

#### Output analysis

After analyzing the outputs of the first and second commands, I realized that the `-fc` flag did not affect anything in this case. The difference in the reports was only in the line using the filter (` :: Filter           : Response status: 404`).

#### Accessible directories:

- `config` (status 301)

- `docs` (statu 301)

- `external` (statu 301)

#### Interesting error codes:

- `server-status` (ststus 403)

- Unknown `er` (ststus 302)

## Task 2 - Python Fuzzing

### Install AFL++ (`python-afl`) locally and setup docker

I had some problems configuring docker. Docker was running properly, but the `input` and `output` folders weren't working properly, so I modified the command a bit to make everything work correctly.

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task2_img/install.png)

### Prepare `input` and `output` directory with appropriate test input

As I described earlier, due to some problems, I decided to create folders in `/src/` on my computer. I also created some simple tests:

- Simple %-encoding ("A")
  
- Space encoding

- No encoding

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task2_img/input.png)

The entire contents of the `input` folder can be viewed at this link: [`input`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/lab4/task2_data/input)

### Run the fuzzer

After these steps, I launched the fuzzer using the command:

```bash
py-afl-fuzz -i /src/input -o /src/output -- /usr/bin/python3 /src/main.py
```

However, I got an error. I don't fully understand why it occurred, but after adding a timeout to the command, everything worked:

```bash
py-afl-fuzz -i /src/input -o /src/output -t 2000 -- /usr/bin/python3 /src/main.py
```

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task2_img/error_timeout.png)


### Wait for a while, expect at least one detected crash and one detected hang

I didn't wait very long. Due to the fact that I located the `input` and `output` folders in `/src/`, I could check their contents from another running terminal. Therefore, as soon as I saw that the contents appeared in the `crashes` and `hangs` folders, I stopped fuzzing.

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task2_img/output.png)

The entire contents of the `output` folder can be viewed at this link: [`output`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/lab4/task2_data/output/default)

### Analyze the results

#### `fuzzer_stats`, some `crashes`, and `hangs`:

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task2_img/stat.png)

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task2_img/output.png)

Full report and all data received:

- [`fuzzer_stats`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task2_data/output/default/fuzzer_stats)

- [`crashes`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/lab4/task2_data/output/default/crashes)

- [`hangs`](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/lab4/task2_data/output/default/hangs)

#### Program `crash`

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task2_img/crash.png)

**Error:** ValueError: invalid literal for int() with base 16: '\udcbe'

**Reason:** The decoder tries to interpret Unicode character '\udcbe' as hex digits

**Possible fix:** I think you can just do a simple check on the input data and this will help solve the problem. For example like this:

```bash
if s[i] == '%':
    if i+2 > len(s):
        raise ValueError("Error")
    if not (s[i+1] in '0123456789abcdefABCDEF' and 
            s[i+2] in '0123456789abcdefABCDEF'):
        raise ValueError("Error")
```

#### Program `hang`

When I launched this `hang`, I waited and nothing changed. There were no errors or warnings, but I had to stop this check by pressing `Ctrl+C`. After that, I realized that there was no mistake, but an infinity loop was forming somewhere.

![image](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task2_img/hang.png)

**Reason:** Upon closer examination, I realized that the problem is contained in the indexes. In the case where there is a `+` in the input value, the index does not increase, which forces the code to endlessly perform the same check.

**Possible fix:** I think that you just need to additionally check the index at the beginning, as I showed earlier, and, most importantly, do not forget to increase it (when checking `s[i] == '+'`).

```bash
if s[i] == '%':
    if i+2 > len(s):
        raise ValueError("Error")
...
elif s[i] == '+':
    ret.append(' ')
    i += 1
```

### Answers to questions

#### Will the fuzzer ever terminate in the above experiment? Why/Why not?

#### How coverage-guided fuzzers work? Is AFL coverage-guided?

#### How to optimize a fuzzing campaign?
