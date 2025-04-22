#!/usr/bin/env python3
import os
import sys
import requests
import subprocess
from pathlib import Path
import tarfile
import zipfile
import shutil


# A class that stores all the information and functions for activating all stages of the script
class AutomatedFirmware:

    # Initialization
    def __init__(self, url, login=None, password=None, device_serial=None, keep_files=False):

        # Introductory data
        self.url = url
        self.login = login
        self.password = password
        self.device_serial = device_serial

        # A variable that allows you to enable or disable cleaning after the script (it was created to fix script bugs)
        self.keep_files = keep_files

        # Variables for working with files
        self.temp_dir = Path('firmware_temp_dir')
        self.archive_path = None
        self.extract_dir = None

    # The function for downloading the archive from the link
    def download_file(self):
        print(f"Downloading the archive via the link...")
        self.archive_path = self.temp_dir / self.url.split('/')[-1]

        # In fact, this feature is not needed right now, because it is only used if file cleanup is disabled
        if self.archive_path.exists():
            print(f"Archive already exists at {self.archive_path}.")
            return True

        # Download the archive from the link
        try:
            auth = (self.login, self.password) if (self.login and self.password) else None
            with requests.get(self.url, auth=auth, stream=True) as r:
                r.raise_for_status()
                with open(self.archive_path, 'wb') as f:
                    for chunk in r.iter_content(chunk_size=8192):
                        f.write(chunk)
            print(f"Download completed successfully!")
            print(f"The path to the installed archive: {self.archive_path}.")
            return True
        except Exception as e:
            print(f"Download failed.")
            print(f"Error: {str(e)}.", file=sys.stderr)
            return False

    # Extract files from an archive
    def extract_archive(self):

        # Just in case, check if there are any errors to the paths in the files
        if not self.archive_path or not self.archive_path.exists():
            raise FileNotFoundError("Archive file not found.")

        # Creating a separate folder for extracting data from the archive
        self.extract_dir = self.temp_dir / 'extracted'
        self.extract_dir.mkdir(parents=True, exist_ok=True)
        print(f"Extracting {self.archive_path} to {self.extract_dir}...")
        archive_name = str(self.archive_path).lower()

        # Extract data from archives (following the formats that were specified)
        try:
            if archive_name.endswith('.tar.bz2') or archive_name.endswith('.tbz2'):
                with tarfile.open(self.archive_path, 'r:bz2') as tar:
                    tar.extractall(self.extract_dir)

            elif archive_name.endswith('.tar.gz') or archive_name.endswith('.tgz'):
                with tarfile.open(self.archive_path, 'r:gz') as tar:
                    tar.extractall(self.extract_dir)

            elif archive_name.endswith('.tar'):
                with tarfile.open(self.archive_path, 'r:') as tar:
                    tar.extractall(self.extract_dir)

            elif archive_name.endswith('.zip'):
                with zipfile.ZipFile(self.archive_path, 'r') as zip_ref:
                    zip_ref.extractall(self.extract_dir)

            else:

                # Try to extract an unknown extension
                try:
                    with tarfile.open(self.archive_path, 'r:*') as tar:
                        tar.extractall(self.extract_dir)
                except:
                    raise ValueError(f"Unsupported archive format: {self.archive_path}.")

            print("Extraction completed successfully!")
            return True

        except Exception as e:
            print(f"Extraction failed.")
            print(f"Error: {str(e)}.", file=sys.stderr)
            return False

    # Search flash.sh in the extracted files
    def find_flash(self):
        for root, dirs, files in os.walk(self.extract_dir):
            if 'flash.sh' in files:
                flash_script = Path(root) / 'flash.sh'

                # Ensure it is executable
                os.chmod(flash_script, 0o755)
                return flash_script
        raise FileNotFoundError("`flash.sh` not found in extracted files.")

    # Execute the flash script with optional device serial
    def run_flash(self, flash_script):
        print(f"Running flash script: {flash_script}.")

        # To flash a device with a serial number
        # If the device_serial field is not specified, there will most likely be an error
        cmd = [str(flash_script)]
        if self.device_serial:
            cmd.extend(['--extra-opts', '-s', self.device_serial])

        try:
            subprocess.run(cmd, check=True)
            return True
        except subprocess.CalledProcessError as e:
            print(f"Flash script failed.")
            print(f"Error: {str(e)}.", file=sys.stderr)
            return False

    # Reboot device
    def reboot(self):
        print("Rebooting device...")
        try:
            subprocess.run(['fastboot', 'reboot'], check=True)
            return True
        except subprocess.CalledProcessError as e:
            print(f"Reboot failed: {str(e)}", file=sys.stderr)
            return False
        except FileNotFoundError:
            print("Error: fastboot command not found", file=sys.stderr)
            return False

    # Remove temporary files
    def cleanup(self):
        if not self.keep_files and self.temp_dir.exists():
            print("Cleaning up temporary files...")
            shutil.rmtree(self.temp_dir)

    # Executing the entire script for automatic firmware
    def run(self):
        try:

            # Setup temporary directory
            self.temp_dir.mkdir(exist_ok=True)
            self.archive_path = self.temp_dir

            # Download the archive
            if not self.download_file():
                return False

            # Extract the archive
            if not self.extract_archive():
                return False

            # Find and run flash script
            flash_script = self.find_flash()
            if not self.run_flash(flash_script):
                return False

            # Reboot device
            if not self.reboot():
                return False
            return True

        except Exception as e:
            print(f"Error: {str(e)}", file=sys.stderr)
            return False
        finally:
            self.cleanup()


def main():

    # Сonfiguration - replace with your values
    config = {
        'url': "https://...",  # Archive installation link
        'login': None,  # Set your username if required
        'password': None,  # Set your password if required
        'device_serial': None,  # Set device serial
        'keep_files': False  # Set to "True" to keep temporary files (I recommend changing it to "True" only in case of script debugging or for manual verification)
    }

    flasher = AutomatedFirmware(
        url=config['url'],
        login=config['login'],
        password=config['password'],
        device_serial=config['device_serial'],
        keep_files=config['keep_files']
    )

    if flasher.run():
        print("Firmware flashing completed successfully!")
        sys.exit(0)
    else:
        print("Firmware flashing failed.", file=sys.stderr)
        sys.exit(1)


if __name__ == '__main__':
    main()