# Secure System Development - Lab 1

**Student**: Egor Valikov

**Group**: B22-CBS-01

**Email**: e.valikov@innopolis.university

**Telegram**: @EgorValikov

## Introduction

I chose to use Docker containers for this lab work for several reasons:

- **Docker simplifies the process of setting up**, launching, and deleting containers without requiring complex virtual machine configuration.
- **Containers start quickly**, whereas virtual machines (VMs) take time to load the operating system. This means that it unfolds faster.
- **Reduced resource usage**: virtual machines (VMs) build full-fledged operating systems, which demand more RAM and CPU, while containers use the host core.
- **Updating and restoring is simpler** because you can simply recreate the container in case something goes wrong.

## Task 1 - Setup GitLab Server

### Creating a `docker-compose.yml` for GitLab

1. Create a working directory and go to it:

```bash
mkdir -p ~/gitlab
cd ~/gitlab
```

2. Create a `docker-compose file.yml`:

```bash
nano docker-compose.yml
```

3. Write code for `docker-compose.yml`:

I accidentally named the running container as `<id>-gitlab`, where `<id>` is my nickname on github, not my student ID or my Telegram alias (I'm sorry, I reread this rule only during writing the report, but this will not affect the further work of the server and runner).

```yml
version: '3.8'

services:
  gitlab:
    image: gitlab/gitlab-ce:latest
    container_name: zDragonLORD1010-gitlab
    restart: always
    hostname: gitlab.test.local
    ports:
      - "80:80"
      - "22:22"
    environment:
      GITLAB_OMNIBUS_CONFIG: |
        external_url 'http://gitlab.test.local'
        gitlab_rails['gitlab_shell_ssh_port'] = 22
    volumes:
      - ./config:/etc/gitlab
      - ./logs:/var/log/gitlab
      - ./data:/var/opt/gitlab
    networks:
      - gitlab-net

networks:
  gitlab-net:
    driver: bridge
```

#### The purpose of `docker-compose.yml` file:

- GitLab CE is being connected
- Gives the container the name **zDragonLORD1010-gitlab**
- Opens ports 80 (Web) and 22 (SSH)
- Creates a local DNS `gitlab.test.local`
- Mounts folders for data storage

---

### Launch the Server container

1. Launching the GitLab server:

```bash
egor@egor-100-HP:~/gitlab$ sudo docker-compose up -d
[sudo] password for egor: 
[+] Running 10/10
 ✔ gitlab 9 layers [⣿⣿⣿⣿⣿⣿⣿⣿⣿]      0B/0B      Pulled                    318.7s 
   ✔ 9cb31e2e37ea Pull complete                                            9.4s 
   ✔ eb69150a7819 Pull complete                                            1.1s 
   ✔ befaf65bfcbe Pull complete                                           15.0s 
   ✔ 93017a39a77b Pull complete                                            2.1s 
   ✔ 5fc84e2a9a81 Pull complete                                            3.3s 
   ✔ b5d428a95c32 Pull complete                                            4.3s 
   ✔ 5306bc1d2162 Pull complete                                            5.4s 
   ✔ 56a220db9a03 Pull complete                                            6.4s 
   ✔ a8515d9babcb Pull complete                                          298.0s 
[+] Running 2/2
 ✔ Network gitlab_gitlab-net         Create...                             0.1s 
 ✔ Container zDragonLORD1010-gitlab  Started                               0.7s 
```

2. Check that the container is working:

```bash
egor@egor-100-HP:~/gitlab$ sudo docker ps
CONTAINER ID   IMAGE                     COMMAND             CREATED          STATUS                             PORTS                                                                           NAMES
40e6dd659d5e   gitlab/gitlab-ce:latest   "/assets/wrapper"   20 seconds ago   Up 19 seconds (health: starting)   0.0.0.0:22->22/tcp, :::22->22/tcp, 0.0.0.0:80->80/tcp, :::80->80/tcp, 443/tcp   zDragonLORD1010-gitlab
```

3. Register DNS in `/etc/hosts`

- Open the hosts file:

```bash
sudo nano /etc/hosts
```

- Add a line:

```
127.0.0.1  gitlab.test.local
```

4. Enabling HTTPS (Self-signed cert)

- Installing `mkcert`:

```bash
sudo apt install libnss3-tools -y
curl -L https://github.com/FiloSottile/mkcert/releases/latest/download/mkcert-v1.4.4-linux-amd64 -o mkcert
chmod +x mkcert
sudo mv mkcert /usr/local/bin/
```

- Create self-signed certificates

```bash
mkcert -install
mkcert -key-file cert.key -cert-file cert.pem gitlab.test.local
```

- After execution, two files will appear in the current folder.:
  - `cert.pem` – certificate
  - `cert.key` – key

- Modify the `docker-compose.yml`:

```yml
version: '3.8'

services:
  gitlab:
    image: gitlab/gitlab-ce:latest
    container_name: zDragonLORD1010-gitlab
    restart: always
    hostname: gitlab.test.local
    ports:
      - "80:80"
      - "443:443"
      - "22:22"
    environment:
      GITLAB_OMNIBUS_CONFIG: |
        external_url 'https://gitlab.test.local'
        gitlab_rails['gitlab_shell_ssh_port'] = 22
    volumes:
      - ./config:/etc/gitlab
      - ./logs:/var/log/gitlab
      - ./data:/var/opt/gitlab
      - ./cert.pem:/etc/gitlab/ssl/gitlab.test.local.crt
      - ./cert.key:/etc/gitlab/ssl/gitlab.test.local.key
    networks:
      - gitlab-net

networks:
  gitlab-net:
    driver: bridge
```

5. Disabling unnecessary services in `gitlab.rb`

- Editing the GitLab configuration:

```bash
sudo nano ~/gitlab/config/gitlab.rb
```

- Disabling unnecessary services

```rb
# Disable GitLab Pages
gitlab_pages['enable'] = false

# Disable Mattermost
mattermost['enable'] = false

# Disable Container Registry
registry['enable'] = false

# Disable GitLab KAS
gitlab_kas['enable'] = false
```

6. Applying the changes

```bash
sudo docker exec -it zDragonLORD1010-gitlab gitlab-ctl reconfigure
sudo docker restart zDragonLORD1010-gitlab
docker ps
```

(The output is very large, so I inserted only a part)

```bash
egor@egor-100-HP:~$ sudo docker exec -it zDragonLORD1010-gitlab gitlab-ctl reconfigure
[2025-02-17T12:38:13+00:00] INFO: Started Cinc Zero at chefzero://localhost:1 with repository at /opt/gitlab/embedded (One version per cookbook)
Cinc Client, version 18.3.0
Patents: https://www.chef.io/patents
Infra Phase starting
[2025-02-17T12:38:13+00:00] INFO: *** Cinc Client 18.3.0 ***
[2025-02-17T12:38:13+00:00] INFO: Platform: x86_64-linux
[2025-02-17T12:38:13+00:00] INFO: Cinc-client pid: 1689
/opt/gitlab/embedded/lib/ruby/gems/3.2.0/gems/ffi-yajl-2.6.0/lib/ffi_yajl/encoder.rb:42: warning: undefining the allocator of T_DATA class FFI_Yajl::Ext::Encoder::YajlGen
[2025-02-17T12:38:14+00:00] INFO: Setting the run_list to ["recipe[gitlab]"] from CLI options
[2025-02-17T12:38:14+00:00] INFO: Run List is [recipe[gitlab]]
[2025-02-17T12:38:14+00:00] INFO: Run List expands to [gitlab]
[2025-02-17T12:38:14+00:00] INFO: Starting Cinc Client Run for gitlab.test.local
[2025-02-17T12:38:14+00:00] INFO: Running start handlers
[2025-02-17T12:38:14+00:00] INFO: Start handlers complete.
Resolving cookbooks for run list: ["gitlab"]
[2025-02-17T12:38:15+00:00] INFO: Loading cookbooks [gitlab@0.0.1, package@0.1.0, logrotate@0.1.0, postgresql@0.1.0, redis@0.1.0, monitoring@0.1.0, registry@0.1.0, mattermost@0.1.0, consul@0.1.0, gitaly@0.1.0, praefect@0.1.0, gitlab-kas@0.1.0, gitlab-pages@0.1.0, letsencrypt@0.1.0, nginx@0.1.0, runit@5.1.7, acme@4.1.6, crond@0.1.0]
Synchronizing cookbooks:
  - gitlab (0.0.1)
  - package (0.1.0)
  - logrotate (0.1.0)
  - postgresql (0.1.0)
  - redis (0.1.0)
  - monitoring (0.1.0)
  - registry (0.1.0)
  - mattermost (0.1.0)
  - consul (0.1.0)
  - gitaly (0.1.0)
  - praefect (0.1.0)
  - gitlab-kas (0.1.0)
  - gitlab-pages (0.1.0)
  - letsencrypt (0.1.0)
  - nginx (0.1.0)
  - runit (5.1.7)
  - acme (4.1.6)
  - crond (0.1.0)
Installing cookbook gem dependencies:
Compiling cookbooks...
```

--- 

#### After GitLab Server started, I had the following structure:

```bash
gitlab/
├── config/
│   ├── gitlab.rb
│   ├── ssl/
│   ├── trusted-certs/
├── data/
├── logs/
│-- cert.pem
│-- cert.key
├── docker-compose.yml
```

---

### Create an empty repository

Now, after completing the previous steps, we can log in to GitLab.

- Getting the administrator password:

```bash
egor@egor-100-HP:~/gitlab$ sudo docker exec -it zDragonLORD1010-gitlab grep 'Password:' /etc/gitlab/initial_root_password
[sudo] password for egor: 
Password: /SroByRvx+m2QpMsL2LvcKX/HgBUVRKOgTmpq0LR8y4=
```

1. Log in to GitLab

**Url:** https://gitlab.test.local

**Username:** root

**Password:** /SroByRvx+m2QpMsL2LvcKX/HgBUVRKOgTmpq0LR8y4=

2. Create a new repository on `http://gitlab.test.local`

![image](https://github.com/user-attachments/assets/de6e6b9a-489a-48e3-852d-c37e15fa6750)

3. Cloning the repository locally

```bash
egor@egor-100-HP:~$ git clone http://gitlab.test.local/root/zdragonlord1010-repo.git
Cloning into 'zdragonlord1010-repo'...
Username for 'http://gitlab.test.local': zdragonlord1010-repo
Password for 'http://zdragonlord1010-repo@gitlab.test.local': 
warning: You appear to have cloned an empty repository.
```

## Task 1 Results:

| Requirement                                                    | In Stock       | Comment                                                                           |
| -------------------------------------------------------------- | -------------- | --------------------------------------------------------------------------------- |
| Pulls the GitLab CE edition                                    |   True         | `gitlab/gitlab-ce:latest` is installed in `docker-compose.yml`                    |
| Name the running container as `<id>-gitlab`                    |   True         | The container is named **zDragonLORD1010-gitlab**                                 |
| Map container ports **80** and **22** to host machine          |   True         | In `docker-compose.yml` ports **80:80** and **22:22**                             |
| Expose the GitLab server as `gitlab.test.local`                |   True         | In `docker-compose.yml` specified hostname: `gitlab.test.local`                   |
| Update your hosts file to resolve the mentioned DNS record     |   True         | Added to `/etc/hosts`: `127.0.0.1 gitlab.test.local`                              |
| [Bonus] Enable HTTPS using self-signed certs                   |   True         | `mkcert` is installed, `cert.pem` and `cert.key` are created, HTTPS is configured |
| Bind necessary directories (logs, app data, configs...)        |   True         | Added `./config`, `./logs`, and `./data` to the container volumes                 |
| Find out how to disable unneeded services                      |   True         | **Registry, Mattermost, GitLab Pages, GitLab KAS** are disabled in `gitlab.rb`    |
| Run the docker-compose file and make sure configs are working  |   True         | The container is running, the status is **healthy**, GitLab is available          |
| Create an empty repo named `<id>-repo`                         |   True         | The `zdragonlord1010-repo` repository was created and successfully cloned         |

## Task 2 - Setup GitLab Runner

### What is the GitLab Runner Executor?

An executor in GitLab Runner determines how a job is run. Different executors handle different environments and configurations. The common executors include:

- **Shell**: Runs jobs locally on the machine where GitLab Runner is installed.
- **Docker**: Runs jobs inside Docker containers.
- **VirtualBox**: Runs jobs inside VirtualBox virtual machines.
- **Parallels**: Runs jobs inside Parallels virtual machines.
- **SSH**: Runs jobs on remote machines over SSH.
- **Kubernetes**: Runs jobs inside Kubernetes pods.

### Setup and register GitLab Runner

I setup and register GitLab Runner using guide from gitlab for linux (https://docs.gitlab.com/runner/register/#register-with-a-runner-registration-token-deprecated):

1. Download and install binary

```bash
sudo curl -L --output /usr/local/bin/gitlab-runner https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-linux-amd64
```

2. Give it permission to execute

```bash
sudo chmod +x /usr/local/bin/gitlab-runner
```

3. Create a GitLab Runner user

```bash
sudo useradd --comment 'GitLab Runner' --create-home gitlab-runner --shell /bin/bash
```

4. Install and run as a service

```bash
sudo gitlab-runner install --user=gitlab-runner --working-directory=/home/gitlab-runner
sudo gitlab-runner start
sudo gitlab-runner register --url https://gitlab.test.local/ --registration-token GR1348941szHvhP-BQw9dCU2UwyHz
```

```bash
egor@egor-100-HP:~/gitlab-runner$ sudo gitlab-runner register --url https://gitlab.test.local/ --registration-token GR1348941szHvhP-BQw9dCU2UwyHz
Runtime platform                                    arch=amd64 os=linux pid=39886 revision=690ce25c version=17.8.3
Running in system-mode.                            
                                                   
Enter the GitLab instance URL (for example, https://gitlab.com/):
[https://gitlab.test.local/]: 
Enter the registration token:
[GR1348941szHvhP-BQw9dCU2UwyHz]: 
Enter a description for the runner: zDragonLORD1010-runner
[egor-100-HP]: zDragonLORD1010-runner
Enter tags for the runner (comma-separated):
zDragonLORD1010-runner
Enter optional maintenance note for the runner:

WARNING: Support for registration tokens and runner parameters in the 'register' command has been deprecated in GitLab Runner 15.6 and will be replaced with support for authentication tokens. For more information, see https://docs.gitlab.com/ee/ci/runners/new_creation_workflow 
Registering runner... succeeded                     runner=GR1348941szHvhP-B
Enter an executor: docker+machine, docker-autoscaler, instance, ssh, virtualbox, parallels, docker, docker-windows, kubernetes, custom, shell:
shell
Runner registered successfully. Feel free to start it, but if it's running already the config should be automatically reloaded!
 
Configuration (with the authentication token) was saved in "/etc/gitlab-runner/config.toml" 
```

```bash
egor@egor-100-HP:~/gitlab-runner$ sudo docker ps
CONTAINER ID   IMAGE                         COMMAND                  CREATED          STATUS                 PORTS                                                                                                         NAMES
4880dfeacf5f   gitlab/gitlab-runner:latest   "/usr/bin/dumb-init …"   26 seconds ago   Up 26 seconds                                                                                                                        gitlab-runner
7539d184486a   gitlab/gitlab-ce:latest       "/assets/wrapper"        2 hours ago      Up 2 hours (healthy)   0.0.0.0:22->22/tcp, :::22->22/tcp, 0.0.0.0:80->80/tcp, :::80->80/tcp, 0.0.0.0:443->443/tcp, :::443->443/tcp   zDragonLORD1010-gitlab
```

![image](https://github.com/user-attachments/assets/81768b06-3a78-437c-9485-5091bf834e20)

## Task 2 Results:

| Requirement                                                                       | In Stock       | Comment                                                                           |
| --------------------------------------------------------------------------------- | -------------- | --------------------------------------------------------------------------------- |
| Set up the GitLab Runner in the same network as GitLab server                     |   True         | Runner runs on the `gitlab-net` network together with the server                  |
| Explain what is the GitLab Runner executor and set the executor type to shell     |   True         | **Executor** is the CI/CD execution method, `shell` is installed                  |
| Set GitLab Runner tag to `<id>-runner`                                            |   True         | The `zDragonLORD1010-runner` tag has been added, it is displayed in GitLab        |
| Register your GitLab runner with the GitLab server. validate that it's connected  |   True         | Runner is registered, it is **"Online"** in GitLab                                |

## Task 3 - Setup GitLab SAST

### Setup GitLab SAST

1. Cloning DVWA:

```bash
git clone https://github.com/digininja/DVWA.git
cd DVWA
```

2. Deleting it .git and push it to your repository:

```bash
rm -rf .git
git init
git config --global user.name "Egor Valikov"
git config --global user.email "e.valikov@innopolis.university"
git remote add origin https://gitlab.test.local/root/zdragonlord1010-repo.git
git add .
git commit -m "DVWA"
git push -u origin master
```

3. Adding it `.gitlab-ci.yml` for launching Semgrep:

```yml
stages:
  - test

sast:
  image: returntocorp/semgrep
  stage: test
  script:
    - semgrep --config=auto --json -o result.json .
  artifacts:
    paths:
      - result.json
    expire_in: 1 week
```

4. Launching CI/CD:

```bash
git add .
git commit -m "Final"
git push origin master
```

![image](https://github.com/user-attachments/assets/03ae8ad6-37db-44b3-8f4e-4f903572d6e4)

![image](https://github.com/user-attachments/assets/17e0d307-ecd0-4259-9efa-e67d02346241)

![image](https://github.com/user-attachments/assets/2be8d5ef-0364-4125-a81b-a2fce6583592)

--- 

### Checking the report `result.json`:

1. After completing the pipeline, log in to **GitLab → CI/CD → Pipelines → Latest Job → Download Artifacts** (This is only a small part of the `result.json`. I've attached the full `result.json` to the moodle report):

```json
{
  "errors": [
    {
      "code": 3,
      "level": "warn",
      "message": "Syntax error at line Dockerfile:24:\n `RUN cd /var/www/html/vulnerabilities/api \\\n && composer install \\\n` was unexpected",
      "path": "Dockerfile",
      "spans": [
        {
          "end": {
            "col": 24,
            "line": 25,
            "offset": 66
          },
          "file": "Dockerfile",
          "start": {
            "col": 1,
            "line": 24,
            "offset": 0
          }
        }
      ],
      "type": [
        "PartialParsing",
        [
          {
            "end": {
              "col": 24,
              "line": 25,
              "offset": 66
            },
            "path": "Dockerfile",
            "start": {
              "col": 1,
              "line": 24,
              "offset": 0
            }
          }
        ]
      ]
    },
    {
      "code": 3,
      "level": "warn",
      "message": "Syntax error at line docs/pdf.html:1:\n `Damn Vulnerable Web Application (DVWA)` was unexpected",
      "path": "docs/pdf.html",
      "spans": [
        {
          "end": {
            "col": 39,
            "line": 1,
            "offset": 38
          },
          "file": "docs/pdf.html",
          "start": {
            "col": 1,
            "line": 1,
            "offset": 0
          }
        }
      ],
      "type": [
        "PartialParsing",
        [
          {
            "end": {
              "col": 39,
              "line": 1,
              "offset": 38
            },
            "path": "docs/pdf.html",
            "start": {
              "col": 1,
              "line": 1,
              "offset": 0
            }
          }
        ]
      ]
    },
    {
      "code": 3,
      "level": "warn",
      "message": "Syntax error at line .github/workflows/docker-image.yml:22:\n When parsing a snippet as Bash for metavariable-pattern in rule 'yaml.github-actions.security.curl-eval.curl-eval', `${{` was unexpected",
      "path": ".github/workflows/docker-image.yml",
      "spans": [
        {
          "end": {
            "col": 33,
            "line": 22,
            "offset": 425
          },
          "file": ".github/workflows/docker-image.yml",
          "start": {
            "col": 30,
            "line": 22,
            "offset": 422
          }
        },
        {
```

2. Server-Side Request Forgery (SSRF) vulnerability in `instructions.php`

The report identifies an **SSRF vulnerability** in the following line of code (527 line):

```php
"lines": "$instructions = file_get_contents( DVWA_WEB_PAGE_TO_ROOT.$readFile );",
```

  - The variable `$readFile` is derived from `$_GET`, meaning it can be controlled by an attacker.
  - This allows an attacker to craft a malicious URL that could make unauthorized requests to internal or external systems.

**Mitigation**:

  - Validate and sanitize user input before using it in file operations.
  - Use a whitelist approach to allow only specific files to be accessed.
  - If fetching remote resources is necessary, restrict it to trusted sources.

Example of safer implementation:

```php
$allowed_files = ['instructions1.txt', 'instructions2.txt'];
if (in_array($readFile, $allowed_files)) {
    $instructions = file_get_contents(DVWA_WEB_PAGE_TO_ROOT . $readFile);
} else {
    die('Access Denied');
}
```

This ensures only pre-approved files can be accessed, preventing an attacker from exploiting this vulnerability.

## Task 3 Results:

| Requirement                                                                                      | In Stock       | Comment                                                             |
| ------------------------------------------------------------------------------------------------ | -------------- | ------------------------------------------------------------------- |
| Clone a vulnerable-by-design app of your choice                                                  |   True         | `DVWA` was cloned and used for testing                              |
| Remove the `.git` from the cloned app and re-push it to a repo created in Task 1                 |   True         | `.git` directory was removed, and the code was pushed to `zdragonlord1010-repo` |
| Add a `.gitlab-ci.yml` to the repo that runs Semgrep scan and collects the report as an artifact |   True         | `.gitlab-ci.yml` was created, and Semgrep runs successfully during CI/CD |
| Test the CI, verify it runs on every push to the main branch                                     |   True         | Pipeline is triggered on every push to the `master` branch, running Semgrep automatically  |
| Check the generated report, explain one finding, and suggest mitigation                          |   True         | **SSRF vulnerability** was identified; mitigation involves input validation and whitelisting  |
