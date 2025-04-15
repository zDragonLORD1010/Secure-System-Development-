# Lab 5 - Web Application Firewall (WAF)

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/lab5/lab5_Report_Egor_Valikov.md

## Task 1 - Blocking SQLi with WAF

### Deploy Juice-Shop on port 3000 and exploit vulnerability

The first thing I did was launch docker. Then I created a vulnerable SQL code to login as `admin`:

```bash
admin' OR 1=1--
```

![image](https://github.com/user-attachments/assets/7a1171ed-2b9d-4d5b-930f-2adf718e5b59)

![image](https://github.com/user-attachments/assets/c6137802-6bf6-4a33-ab0a-a945123ef183)

![image](https://github.com/user-attachments/assets/98f55cdf-ee4b-4171-93ce-e262002c9e45)

![image](https://github.com/user-attachments/assets/31c6702d-4f94-40e9-83f4-5d89c817a723)

This way I was able to log in to the `admin` account.

### Deploy OWASP ModSecurity+CRS for Nginx in front of the Juice-Shop on port 8080

First of all, I created an docker container `docker-compose.yml` and created the code to launch the Juice-Shop application with the OWASP ModSecurity+CRS.

![image](https://github.com/user-attachments/assets/ae7be1fb-b174-4f6a-8546-a484732f0332)

![image](https://github.com/user-attachments/assets/c8d6fee8-73c9-4ccf-92cb-05b130197e33)

Thus, the Juice-Shop application using the OWASP ModSecurity+CRS no longer allowed me to log in as an `admin`.

![image](https://github.com/user-attachments/assets/b7da1cbf-56f9-40e2-aab3-42090f049ded)

## Task 2 - Bypassing WAF

### Deploy Juice-Shop with the WASP ModSecurity+CRS on port 8080 and exploit vulnerability

For this task, I used a docker container `docker-compose.yml` that was created earlier in the first task. After a long search, I found a new SQL code that helped me log in as an `admin` even using the OWASP ModSecurity+CRS:

```bash
admin' /? or true --
```

![image](https://github.com/user-attachments/assets/3cb44e20-5d7d-4d9b-8406-595b35ac4829)

![image](https://github.com/user-attachments/assets/3e1fdec7-44e6-496e-a798-02a0866c8ff4)

### Re-Configure WAF to block the updated exploit

I had to create new rules `custom_rules.conf` to block the new exploit. I spent a lot of time making them work correctly and was eventually able to block a vulnerability related to the previous SQL code. Of the most important things, I've created three new rules:

- Block SQLi Bypasses
- Block mixed patterns
- Block encoded payloads

Due to the fact that the `nano` and `vi` commands did not work, I had to write down the new rules through the `echo` command.

![image](https://github.com/user-attachments/assets/f0f99b20-df92-4ec3-a3fe-767244642038)

![image](https://github.com/user-attachments/assets/3f04cc7e-41d7-4c7b-b2d9-b11745303621)

![image](https://github.com/user-attachments/assets/6f1296cf-3a91-47d7-b41a-fedb486bd384)

![image](https://github.com/user-attachments/assets/0690f48b-2c87-4ac9-89f7-4a78791c6e46)

After applying the new rules, I became made sure that this vulnerable SQL code does not work in any form.

![image](https://github.com/user-attachments/assets/2b95cede-fe12-4828-8179-2ac9f2db0f29)

![image](https://github.com/user-attachments/assets/cded8a4e-9fa3-43cc-a4c7-ac9dd3926633)

![image](https://github.com/user-attachments/assets/2e6a8e31-d32a-4c66-a4f2-41b47b5253e0)





