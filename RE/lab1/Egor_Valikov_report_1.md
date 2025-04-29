# ESP32-S2

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab1/Egor_Valikov_report_1.md

## Introduction

The ESP32-S2 is a single-chip system (SoC) designed for energy-efficient applications with a high degree of integration. It is developed by Espressif. These microcontrollers are based on the Xtensa LX7 processor and integrated 2.4 GHz Wi-Fi support. The ESP32-S2 is designed for use in low-power applications, including the Internet of Things (IoT), wearable electronics, and smart homes. This series provides a balance between efficient energy consumption, compact design, safety, high performance, and reliability. A special feature of the ESP32-S2 is the ability to develop applications without the need for an external host microcontroller.

## Architecture and main components

The core of the ESP32-S2 is a high-performance single-core 32-bit Xtensa LX7 processor. This processor is capable of operating at a frequency of up to 240 MHz. Separate buses for data and instructions are provided by the processor architecture. Data and instructions can be accessed simultaneously thanks to this division.

### There are multiple memory types in the ESP32-S2 memory subsystem:

- **ROM:** It has 128 KB of ROM that is used to store the bootloader and other essential programs.     
- **RAM:** Contains 320 KB of SRAM for information and command storage. 
- **RTC:** Contains 16 KB of SRAM in the RTC area, which is used to operate in ultra-low power consumption modes.   
- **External Memory Support:** External SPI/SPI/SPI flash memory and external RAM can be connected to the ESP32-S2.

### The ESP32-S2 has a wide range of integrated peripherals:

- **Wi-Fi:** IEEE 802.11b/g/n compatible built-in 2.4GHz Wi-Fi module.
- **GPIO:** General-purpose I/O ports with up to 43 programmable ports.
- **Touch interface:** Up to 14 I/O ports that can be touched.
- **ADC/DAC:** Digital-to-analog converters (2x8-bit DACs) and analog-to-digital converters (2x12-bit SAR ADCs, up to 20 channels).
- **Timers:** Includes 4 universal 64-bit timers and 3 watchdog timers (2 MWDT, 1 RWDT).
- **LED PWM:** Controller for controlling LEDs (up to 8 channels).
- **Camera Interface:** Supports DVP 8/16 interface for connecting cameras.
- **LCD:** Supports various LCD interfaces (8-bit serial RGB/8080/6800 via SPI2, 8/16/24-bit parallel via I2S).
- **For communication with external devices:**
  - **USB OTG:** Enables device or host mode operation.
  - **I2C:** Supports serial data transfer protocol.
  - **I2S:** Supports an interface for transmitting and receiving digital audio data.
  - **SPI:** Supports peripheral interface in master and slave modes.
  - **UART:** Universal asynchronous transceiver for serial communication.
- **Temperature sensor**
- **RMT (Remote control transceiver)**
- **PCNT (Pulse counter)**
- **SDM (Sigma-delta modulation)**
- **TWAI (Two-wire car interface)**
- **HMAC:** An algorithm for calculating the message authentication code based on a hash function.
- **DS (Digital signature module)**
- **RNG (Random number generator)**

## Memory map analysis

### The built-in memory of the ESP32-S2 is divided into several regions:

| Type of memory | Addresses | Type of bus | Access control |
|----------------|--------------------|----------------|----------|
| RTC FAST memory   |  0x3FF9E000 - 0x3FF9FFFF |  Data              |  YES
| Internal ROM 1    |  0x3FFA0000 - 0x3FFAFFFF |  Data              |  NO
| Internal SRAM 0   |  0x3FFB0000 - 0x3FFB7FFF |  Data              |  YES
| Internal SRAM 1   |  0x3FFB8000 - 0x3FFFFFFF |  Data              |  YES
| Internal ROM 0    |  0x40000000 - 0x4000FFFF |  Instructions      |  NO
| Internal ROM 1    |  0x40010000 - 0x4001FFFF |  Instructions      |  NO
| Internal SRAM 0   |  0x40020000 - 0x40027FFF |  Instructions      |  YES
| Internal SRAM 1   |  0x40028000 - 0x4006FFFF |  Instructions      |  YES
| RTC FAST memory   |  0x40070000 - 0x40071FFF |  Instructions      |  YES
| RTC SLOW Memory   |  0x50000000 - 0x50001FFF |  Data/Instructions |  YES

### The external memory includes:

- **ICache:** 0x3F000000 - 0x3F3FFFFF
- **DCache:** 0x3F500000 - 0x3FF7FFFF
- **ICache:** 0x40080000 - 0x407FFFFF

## Protection mechanisms

1. **Secure Boot.** Ensures that only authenticated software can be run on the device:

- Guarantees the execution of only verified code. 
- A chain of trust is used with verification of digital signatures at each stage of the download. 
- RSA-PSS with 3072-bit keys is used, the public key is stored in eFuse. 
- Supports revocation of keys.

2. **Flash Encryption.** Used to encrypt the contents of external flash memory, protecting code and data at rest:

- Encrypts external Flash using AES-256-XTS. 
- The key is stored in eFuse and is accessible only by hardware.
- Encryption is transparent to applications and takes place through the MMU cache.

3. **Digital Signature Peripheral.** Used for secure device identification, TLS authentication, and other cryptographic operations:

- Generates RSA signatures at the hardware level.
- The private key remains hidden.

4. **Memory Protection.** Prevents code execution in invalid areas and protects against buffer overflow vulnerabilities:

- Controls access to memory and peripherals (read/write/execute). 
- When rights are violated, there is an exception.

5. **eFuse.** Hardware storage in which the data is irreversibly written:

- Keys for Secure Boot and encryption.
- Security configurations (JTAG, download, etc.).
- Write and read lock flags.

6. **Wi-Fi security.** Support for modern standards:

- WPA3 (Personal and Enterprise).
- Protected Management Frames (PMF).
- OWE.
- EAP authentication.

## Boot Process

1. The built—in loader starts from ROM - it is always the same and unchangeable.
2. The ROM loader verifies the digital signature of the next loader in the external flash memory.
3. If the signature is correct, the second—level loader is loaded and executed.
4. The second loader verifies the signature of the main application.
5. If everything is in order, the application starts.

*(If secure download is enabled, each step is verified using an RSA signature)*

## Security and potential vulnerabilities

Despite the good protection, I believe that the ESP32-S2 could potentially contain the following vulnerabilities:

- Secure Boot and Flash Encryption are powerful, but due to the fact that they mostly have to be manually configured, vulnerabilities may appear.

- Error injection attacks are possible, especially if eFuse and keys are not protected.

- Wi-Fi and USB OTG can contain vulnerabilities, especially in host mode.

**I can recommend the following things:**

- Use unique passwords.

- Update and check the firmware.

- Isolate IoT devices on the network.

- Apply the principle of least privilege.

## Conclusion

I believe the ESP32-S2 is an energy efficient and secure microcontroller well suited for IoT devices. It has rich features, built-in USB support, and powerful protection mechanisms. At the same time, it is important to properly configure security and regularly update the firmware to protect against potential vulnerabilities.
