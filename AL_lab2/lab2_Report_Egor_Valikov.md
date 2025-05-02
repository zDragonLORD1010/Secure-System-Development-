# Lab 2 - GDB

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab2/lab2_Report_Egor_Valikov.md

## Introduction

In this lab, we explore reverse engineering and debugging techniques using tools such as `gdb`, `strace`, `ghidra`, and `ldd`. The goal is to analyze the provided application, which requires a `license key` to run. The `license key` is generated using the hardware identifier and stored somewhere in the file system.

## Launching and checking the functions of the `hack_app` application

Initially, I had some problems launching `hack_app` due to the lack of `libssl1.1` in the system. Therefore, I spent some time fixing this error:

![image](https://github.com/user-attachments/assets/0bc87359-9520-46b5-8e98-5b3493cfcc2d)

![image](https://github.com/user-attachments/assets/0abb1596-397f-4c23-a386-143dfdcf9a4d)

![image](https://github.com/user-attachments/assets/c346e30a-b690-4b33-a6c7-d72172a1368f)

### Next, I found out how the app works:

1. Displays the message `"Welcome to Lab 2 super secure program!"`.

2. Then it displays a message in which a unique `HWID` is generated based on the computer data and asks you to enter the `license key`.

3. After that, there are several options for the development of events:

- If the `license key` is entered correctly, the program displays the message `"Now your app is activated! Thanks for purchasing!"`. Moreover, upon further attempts to launch the program, it will display the message `"Your app is licensed to this PC!"`, which indicates that you have successfully entered the correct `license key`.
- If the `license key` is entered incorrectly, the program will display the message `"Provided key is wrong! App is closing!"`.

4. At the end, the program always outputs the message `"Press Enter to continue..."` and waits for the `Enter` key to be pressed.
