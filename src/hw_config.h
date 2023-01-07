#ifndef _HW_CONFIG_H_
#define _HW_CONFIG_H_

#define FSROOT "/fs"

/* M5Stack */
#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)

    // Uncomment one of below, M5Stack support SPIFFS and SD
    #define FILESYSTEM_BEGIN         \
        SPIFFS.begin(false, FSROOT); \
        FS filesystem = SPIFFS;
    // #define FILESYSTEM_BEGIN SD.begin(4, SPI, 40000000, FSROOT); FS filesystem = SD;

    /* enable audio */
    #define HW_AUDIO
    #define HW_AUDIO_SAMPLERATE 22050

    /* controller is I2C M5Stack CardKB */
    #define HW_CONTROLLER_I2C_M5CARDKB

    #define TFT_BRIGHTNESS 255 /* 0 - 255 */
    #define TFT_BL 32

    /* Display initialisation */
    #define DISPLAY_INIT         \
        Arduino_DataBus *bus = new Arduino_ESP32SPI(27 /* DC */, 14 /* CS */, SCK, MOSI, MISO);  \
        Arduino_ILI9341_M5STACK *gfx = new Arduino_ILI9341_M5STACK(bus, 33 /* RST */, 1 /* rotation */);

/* Odroid-Go */
#elif defined(ARDUINO_ODROID_ESP32)

    // Uncomment one of below, ODROID support SPIFFS and SD
    #define FILESYSTEM_BEGIN         \
        SPIFFS.begin(false, FSROOT); \
        FS filesystem = SPIFFS;
    // #define FILESYSTEM_BEGIN SD.begin(SS, SPI, 40000000, FSROOT); FS filesystem = SD;

    /* enable audio */
    #define HW_AUDIO
    #define HW_AUDIO_SAMPLERATE 22050

    /* controller is GPIO */
    #define HW_CONTROLLER_GPIO
    #define HW_CONTROLLER_GPIO_ANALOG_JOYSTICK
    #define HW_CONTROLLER_GPIO_UP_DOWN 35
    #define HW_CONTROLLER_GPIO_LEFT_RIGHT 34
    #define HW_CONTROLLER_GPIO_SELECT 27
    #define HW_CONTROLLER_GPIO_START 39
    #define HW_CONTROLLER_GPIO_A 32
    #define HW_CONTROLLER_GPIO_B 33
    #define HW_CONTROLLER_GPIO_X 13
    #define HW_CONTROLLER_GPIO_Y 0

    #define TFT_BRIGHTNESS 191 /* 0 - 255 */
    #define TFT_BL 14

    /* Display initialisation */
    #define DISPLAY_INIT         \
        Arduino_DataBus *bus = new Arduino_ESP32SPI(21 /* DC */, 5 /* CS */, SCK, MOSI, MISO); \
        Arduino_ILI9341 *gfx = new Arduino_ILI9341(bus, -1 /* RST */, 3 /* rotation */);

/* TTGO T-Watch */
#elif defined(ARDUINO_T) || defined(ARDUINO_TWATCH_BASE) || defined(ARDUINO_TWATCH_2020_V1) || defined(ARDUINO_TWATCH_2020_V2) // TTGO T-Watch

    // TTGO T-watch with game module only support SPIFFS
    #define FILESYSTEM_BEGIN         \
        SPIFFS.begin(false, FSROOT); \
        FS filesystem = SPIFFS;

    /* buzzer audio */
    #define HW_AUDIO_BUZZER
    #define HW_AUDIO_BUZZER_PIN 4
    #define HW_AUDIO_SAMPLERATE 22050 // nofrendo minimum sample rate

    /* controller is GPIO */
    #define HW_CONTROLLER_GPIO
    #define HW_CONTROLLER_GPIO_ANALOG_JOYSTICK
    #define HW_CONTROLLER_GPIO_UP_DOWN 34
    #define HW_CONTROLLER_GPIO_LEFT_RIGHT 33
    #define HW_CONTROLLER_GPIO_SELECT 15
    #define HW_CONTROLLER_GPIO_START 36
    #define HW_CONTROLLER_GPIO_A 13
    #define HW_CONTROLLER_GPIO_B 25
    #define HW_CONTROLLER_GPIO_X 14
    #define HW_CONTROLLER_GPIO_Y 26

    #define TFT_BRIGHTNESS 255 /* 0 - 255 */
    #define TFT_BL 12

    /* Display initialisation */
    #define DISPLAY_INIT         \
        Arduino_DataBus *bus = new Arduino_ESP32SPI(27 /* DC */, 5 /* CS */, 18 /* SCK */, 19 /* MOSI */, -1 /* MISO */);  \
        Arduino_ST7789 *gfx = new Arduino_ST7789(bus, -1 /* RST */, 1 /* rotation */, true /* IPS */, 240, 240, 0, 80); 

/* custom hardware */
#elif defined(HW_LOUD_ESP_E)

    // Uncomment one of below, ESP32 support SPIFFS SD_MMC and SD
    /* FatFS */
    // #define FILESYSTEM_BEGIN FFat.begin(false, FSROOT); FS filesystem = FFat;
    /* SPIFFS */
    #define FILESYSTEM_BEGIN         \
        SPIFFS.begin(false, FSROOT); \
        FS filesystem = SPIFFS;
    /* 1-bit SD mode SD_MMC, always retry once for begin() failed */
    // #define FILESYSTEM_BEGIN (!SD_MMC.begin(FSROOT, true)) && (!SD_MMC.begin(FSROOT, true)); FS filesystem = SD_MMC;
    /* 4-bit SD mode SD_MMC, always retry once for begin() failed */
    // #define FILESYSTEM_BEGIN (!SD_MMC.begin(FSROOT, false)) && (!SD_MMC.begin(FSROOT, false)); FS filesystem = SD_MMC;
    /* SD using default SPI settings */
    // #define FILESYSTEM_BEGIN SD.begin(22 /* SS */, SPI, 8000000, FSROOT); FS filesystem = SD;
    /* SD using custom SPI settings */
    // #define FILESYSTEM_BEGIN                \
    //     SPIClass spi = SPIClass(HSPI);      \
    //     spi.begin(14, 2, 15, 13);           \
    //     SD.begin(13, spi, 8000000, FSROOT); \
    //     FS filesystem = SD;
    // enable audio
    #define HW_AUDIO
    #define HW_AUDIO_EXTDAC
    #define HW_AUDIO_EXTDAC_WCLK 25
    #define HW_AUDIO_EXTDAC_BCLK 26
    #define HW_AUDIO_EXTDAC_DOUT 22
    #define HW_AUDIO_SAMPLERATE 22050

    /* controller is GPIO */
    #define HW_CONTROLLER_GPIO
    #define HW_CONTROLLER_GPIO_ANALOG_JOYSTICK
    #define HW_CONTROLLER_GPIO_REVERSE_UD
    #define HW_CONTROLLER_GPIO_UP_DOWN 35
    #define HW_CONTROLLER_GPIO_REVERSE_LF
    #define HW_CONTROLLER_GPIO_LEFT_RIGHT 36
    #define HW_CONTROLLER_GPIO_SELECT 0
    #define HW_CONTROLLER_GPIO_START 39
    #define HW_CONTROLLER_GPIO_A 0
    #define HW_CONTROLLER_GPIO_B 0
    #define HW_CONTROLLER_GPIO_X 0
    #define HW_CONTROLLER_GPIO_Y 0


    /* controller is I2C M5Stack CardKB */
    // #define HW_CONTROLLER_I2C_M5CARDKB

    /* controller is I2C BBQ10Keyboard */
    // #define HW_CONTROLLER_I2C_BBQ10KB

    /* HX8357B */
    // #define TFT_BL 27
    // Arduino_DataBus *bus = new Arduino_ESP32SPI(-1 /* DC */, 5 /* CS */, 18 /* SCK */, 23 /* MOSI */, -1 /* MISO */);
    // Arduino_TFT *gfx = new Arduino_HX8357B(bus, 33, 3 /* rotation */, true /* IPS */);

    /* ST7796 on breadboard */
    // #define TFT_BL 32
    // Arduino_DataBus *bus = new Arduino_ESP32SPI(32 /* DC */, -1 /* CS */, 25 /* SCK */, 33 /* MOSI */, -1 /* MISO */);
    // Arduino_TFT *gfx = new Arduino_ST7796(bus, -1 /* RST */, 1 /* rotation */);

    /* ST7796 on LCDKit */
    // #define TFT_BL 23
    // Arduino_DataBus *bus = new Arduino_ESP32SPI(19 /* DC */, 5 /* CS */, 22 /* SCK */, 21 /* MOSI */, -1 /* MISO */);
    // Arduino_ST7796 *gfx = new Arduino_ST7796(bus, 18, 1 /* rotation */);
    
    #define TFT_BRIGHTNESS 128 /* 0 - 255 */
    // #define TFT_BL -1
    #define TFT_DC 4
    #define TFT_CS 5
    #define TFT_RES 32
    #define TFT_ROTATION 1

    /* Display initialisation */
    /* ST7789 ODROID Compatible pin connection */
    #define DISPLAY_INIT         \
        Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC /* DC */, TFT_CS /* CS */, SCK, MOSI, MISO); \
        Arduino_ST7789 *gfx = new Arduino_ST7789(bus, TFT_RES /* RST */, TFT_ROTATION /* rotation */, false /* IPS */);

#elif defined(HW_ESP_GAMEBOY_A)

    #ifdef FS_SPIFFS
    /* FatFS */
    // #define FILESYSTEM_BEGIN FFat.begin(false, FSROOT); FS filesystem = FFat;
    /* SPIFFS */
    #define FILESYSTEM_BEGIN         \
        SPIFFS.begin(false, FSROOT); \
        FS filesystem = SPIFFS;
    #endif

    #ifdef FS_SD_SPI
    #define SD_CS 27
    /* SD using default SPI settings */
    // #define FILESYSTEM_BEGIN \
    //     SD.begin(SD_CS /* SS */, SPI, 8000000, FSROOT); \
    //     FS filesystem = SD;
    /* SD using custom SPI settings */
    #define FILESYSTEM_BEGIN                \
        SPIClass spi = SPIClass(VSPI);      \
        spi.begin();           \
        SD.begin(SD_CS, spi, 8000000, FSROOT); \
        FS filesystem = SD;
    #endif

    // enable audio
    /* enable audio */
    #define HW_AUDIO
    #define HW_AUDIO_SAMPLERATE 22050

    /* controller is PCF8574 I2C bus extender*/
    #define HW_CONTROLLER_I2C_PCF8574
    #define HW_CONTROLLER_I2C_PCF8574_INT_PIN 35
    #define HW_CONTROLLER_I2C_PCF8574_ADDR 0x38
    
    //#define TFT_BRIGHTNESS 200 /* 0 - 255 */
    #define TFT_BL 2
    #define TFT_DC 4
    #define TFT_CS 5
    #define TFT_RES 32
    #define TFT_ROTATION 1

    /* Display initialisation */
    #define DISPLAY_INIT         \
        Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC /* DC */, TFT_CS /* CS */, SCK, MOSI, MISO); \
        Arduino_ILI9341 *gfx = new Arduino_ILI9341(bus, TFT_RES /* RST */, TFT_ROTATION /* rotation */, false /* IPS */);

#endif /* custom hardware */

#endif /* _HW_CONFIG_H_ */
