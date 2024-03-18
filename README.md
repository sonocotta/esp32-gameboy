# ESP32 Gameboy

![Open Source Hardware](/images/open-source-hardware-logo.png)
![Open Source Software](/images/open-source-software-logo.png)

![image](https://github.com/sonocotta/esp32-gameboy/assets/5459747/960ed8a2-596b-4170-a6ab-32de7047de08)

The DIY Gameboy project is an exciting venture for those who have a passion for retro gaming and enjoy hands-on electronics projects. In this project, participants will have the opportunity to construct their own handheld gaming console inspired by the iconic Gameboy.

I started work on the ESP32 Gameboy as a drop-in replacement for the Gameboy case, which is very easy to find on online markets for more than a reasonable price. This project turned out to be not as simple as I expected, spanning across a few board revisions and many issues found and fixed (and a few remain), so at some point, I decided to make a mini version that would use the same code running on the similar but much-simplified hardware, in a shape of DIY kit (I am sure everything gets better when it is a DIY).

Therefore 2 variations of the product were born

# DIY Kit (Play ESP)

This simple kit can be assembled in 5 to 30 minutes (depending on one's skills) and it is as simple as it can be. It runs using Wemos ESP32-S2 of-the-shelf module (with in-package PSRAM) and a truly great 240x240 px LCD screen (it is seriously good by Arduino world standards). It can be powered by two AAA-sized rechargeable batteries to be a true handheld. It has a buzzer for the rudimentary sound system.

## Features

- Lolin ESP32-S2 module
- 1.3' TFT Display 240x240 px (SPI)
- Storage: Internal Flash
- PCF8574 GPIO Expander
- Buzzer
- Step-up converter to pull 3.3V off batteries

| Kit | Assembled |
|---|---|
| ![DSC_0699](https://github.com/sonocotta/esp32-gameboy/assets/5459747/8d480f3c-c626-48c5-b544-145d3ffeadaa) | ![DSC_0727](https://github.com/sonocotta/esp32-gameboy/assets/5459747/a753b13a-2198-4797-8a6a-3fa6c7b00cd0)

## Pinout 

### Screen  

|  | SPI CLK | SPI MOSI | TFT DC | TFT RST | TFT BL |
|---|---|---|---|---|---|
| ESP32-S2 | 7 | 11 | 18 | 5 | 9 |

### PCF8574 GPIO Expander

|  | I2C SDA | I2C SCL | INTR | BUZZER |
|---|---|---|---|---|
| ESP32-S2 | 33 | 35 | 18 | 12 |

## Where to buy

You can support my work by buying this kit at [Tindie](https://www.tindie.com/products/sonocotta/play-esp-diy-kit/))

# Full Gameboy Experience

This is an ESP32-based drop-in replacement for the Gameboy console. 

## Features

- ESP32 WROVER 16M Flash / 8M PSRAM
- 2.8' TFT Display 320x240 px (SPI)
- Storage: Internal Flash or SDCARD
- PCF8574 GPIO Expander
- WS2812 RGB Led
- LM4875 Headphone/Speaker amp with Volume pot
- Li-Ion battery with built-in charger and intelligent power select (When USB is connected)

| Kit | Assembled |
|---|---|
| ![DSC_0515](https://github.com/sonocotta/esp32-gameboy/assets/5459747/6e4ff163-8ee7-46d6-8744-4f4fe4cd12ea) ![DSC_0513](https://github.com/sonocotta/esp32-gameboy/assets/5459747/6fec94a2-db76-42f1-b7a1-fbdb426d2aaa) ![DSC_0519](https://github.com/sonocotta/esp32-gameboy/assets/5459747/63d16ca7-b4c7-4f76-80b4-489928b9b4bd) | ![DSC_0522](https://github.com/sonocotta/esp32-gameboy/assets/5459747/d41ba17f-3b92-4fb3-9dbc-d8877a97f9b1)

## Pinout 

### Screen  

|  | SPI CLK | SPI MOSI | SPI MOSI | TFT CS | TFT DC | TFT RST | TFT BL |
|---|---|---|---|---|---|---|---|
| ESP32 | 18 | 23 | 19 | 5 | 4 | 32 | 2 |

### PCF8574 GPIO Expander

|  | I2C SDA | I2C SCL | INTR | 
|---|---|---|---|
| ESP32 | 21 | 22 | 35 | 

### Other Perihperal

|  | RGB LED | SDCARD CS | AUDIO OUT | CHRG IN | STBY IN | BAT IN |
|---|---|---|---|---|---|---|
| ESP32 | 33 | 27 | 25 | 36 | 39 | 34 |

## Software

In the [software](/firmware/esp32-nes-emulator) section NES firmware is provided. It is based on the [arduino-nofrendo](https://github.com/moononournation/arduino-nofrendo) implementation. Hardware difinition added for both Play ESP and ESP32 Gameboy.

### Platformio IDE
 
Firmware is provided as [Plarformio IDE](https://platformio.org/platformio-ide) projects. After installing it, open the project. Select the proper environment based on your dock. Run the `Build` and `Upload` commands to install necessary tools and libraries, and build and upload the project to the board. Communication and proper upload method selection will be handled by IDE automatically. 

## References

Based heavily on the below work

- [arduino-nofrendo](https://github.com/moononournation/arduino-nofrendo)
- [gbaZero](https://github.com/AEFeinstein/gbaZero)
