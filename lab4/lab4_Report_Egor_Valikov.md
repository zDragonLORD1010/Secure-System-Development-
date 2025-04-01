# Lab 4 - Fuzzing

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/lab4_Report_Egor_Valikov.md

## Task 1 - WebApp Fuzzing

### Installation `ffuf` and `secLists` and run DVWA locally with docker

Initially, I successfully installed `ffuf` and `secLists`. There were no difficulties with this.

![image](https://github.com/user-attachments/assets/474b559c-4589-4f25-9f92-dde7420ca26a)

My next step was to run Run DVWA locally with docker on `127.0.0.1:80:80` (localhost), but there were some problems because this port was already busy. I disabled the previous programs running on this port and successfully launched DVWA.

![image](https://github.com/user-attachments/assets/6d72d036-ef09-4125-bead-7c8d18da5f2c)

![image](https://github.com/user-attachments/assets/a84eae6d-f116-45d9-a5df-c08b0cbe98b3)

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

Second (modofied) command:

```bash
ffuf -u http://localhost:80/FUZZ -w SecLists/Discovery/Web-Content/big.txt -fc 404
```

#### The purpose of the command.

1. Employs `ffuf` for fuzzing the DVWA web application hosted locally.

2. The script iterates through each word in the `big.txt` list, substituting "FUZZ" within the URL for each word.

3. Excludes (`-fc`) any responses that return a 404 status code.

4. Displays only endpoints that can be reached or those that return noteworthy error codes.

#### Executing commands

Running these commands to get reports.

![image](https://github.com/user-attachments/assets/14258134-f480-4db0-9c62-5da561821f57)

![image](https://github.com/user-attachments/assets/6214f7ec-813c-4886-a825-28c1c5583649)

Full output of commands 1 and 2, respectively:

- [`big_output.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_output/big_output.txt)

- [`big_output_filter.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab4/task1_output/big_output_filter.txt)

#### 




### What file extensions from `web-extensions.txt` are available for the index page?




### Which directories from `raft-medium-directories.txt` are accessible? Which ones gave interesting error codes (not 404).





