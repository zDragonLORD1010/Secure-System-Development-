# ESP32-S2

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/RE/lab1/Egor_Valikov_report_1.md

## Introduction

The ESP32-S2 is a single-chip system (SoC) designed for energy-efficient applications with a high degree of integration. It is developed by Espressif. These microcontrollers are based on the Xtensa LX7 processor and integrated 2.4 GHz Wi-Fi support. The ESP32-S2 is designed for use in low-power applications, including the Internet of Things (IoT), wearable electronics, and smart homes. This series provides a balance between efficient energy consumption, compact design, safety, high performance, and reliability. A special feature of the ESP32-S2 is the ability to develop applications without the need for an external host microcontroller.

## Architecture and main components

The core of the ESP32-S2 is a high-performance single-core 32-bit Xtensa LX7 processor. This processor is capable of operating at a frequency of up to 240 MHz. The processor architecture provides separate buses for instructions and data. This separation allows simultaneous access to instructions and data.

### The ESP32-S2 memory subsystem includes several types of memory:

- **ROM:** It contains 128 KB of ROM designed to store the bootloader and basic functions.   
- **RAM:** Includes 320 KB of SRAM for storing data and instructions.   
- **RTC:** Contains 16 KB of SRAM in the RTC area, which is used to operate in ultra-low power consumption modes.   
- **External Memory Support:** ESP32-S2 supports connection of external SPI/SPI/SPI flash memory and external RAM.

### The ESP32-S2 has a wide range of integrated peripherals:

- **Wi-Fi:** Built-in 2.4GHz Wi-Fi module, compatible with IEEE 802.11b/g/n standards.
- **GPIO:** Up to 43 programmable general-purpose I/O ports.
- **Touch interface:** Up to 14 touch-enabled I/O ports.
- **ADC/DAC:** Analog-to-digital converters (2x12-bit SAR ADCs, up to 20 channels) and digital-to-analog converters (2x8-bit DACs).
- **Timers:** Includes 4 universal 64-bit timers and 3 watchdog timers (2 MWDT, 1 RWDT).
- **LED PWM:** Controller for controlling LEDs (up to 8 channels).
- **Camera Interface:** Supports DVP 8/16 interface for connecting cameras.
- **LCD:** Supports various LCD interfaces (8-bit serial RGB/8080/6800 via SPI2, 8/16/24-bit parallel via I2S).
- **For communication with external devices:**
  - **USB OTG:** Provides the ability to work in device or host mode.
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
