# Automated firmware for the device

**Developer:** Egor Valikov

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/test_task/Report.md

## Introduction

This script is designed to automate the device firmware process using firmware archives downloaded from the server. It performs the following tasks:

1. **Download** the firmware archive (with authorization support, if required).

2. **Unpacking** the archive (supported formats .tar.gz, .tar.bz2, .zip).

3. **Running** the firmware script (flash.sh ) with the option to specify the serial number of the device.

4. **Rebooting** the device via fastboot reboot.

5. **Clearing** temporary files after completion.

*p.s. I tried to make the script as clear as possible, so I wrote a lot of comments and tried to make a clear output.*

## Requirements

### System requirements

- A device connected in `fastboot` mode.

- Access to the Internet to download the firmware.

- There is enough disk space to store the archive and unpacked files.

### Software dependencies

-Python 3.6+ (standard library + `requests`):

```bash
pip install requests
```

- Availability of the `fastboot` command in the system

### Pre-launch settings

Before running the script, open the `auto_script.py` and change the following settings in `main()`:

```py
# Сonfiguration - replace with your values
    config = {
        'url': "https://...",  # Archive installation link
        'login': None,  # Set your username if required
        'password': None,  # Set your password if required
        'device_serial': None,  # Set device serial
        'keep_files': False  # Set to "True" to keep temporary files (I recommend changing it to "True" only in case of script debugging or for manual verification)
    }
```

## Instructions for use

1. Fulfill all the requirements listed above.

2. Connect your device in `fastboot` mode.

3. Run the script:

```bash
python3 auto_script.py
```

## What does the script do step by step?

1. Creates the `firmware_temp_dir` folder.

2. Downloads the firmware archive.

3. Unpacks it into the extracted subfolder.

4. Looking for `flash.sh` in the unpacked files.

5. It starts `./flash.sh --extra-opts -s [serial number]`.

6. Reboots the device.

7. Deletes temporary files.

## Link to the full script

[auto_script.py]()


