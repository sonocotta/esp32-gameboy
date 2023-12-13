#include <Arduino.h>

// #ifdef ESP8266
// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #endif
// #ifdef ESP32
// #include <WiFi.h>
// #endif

#ifndef SERIAL_BAUD
#define SERIAL_BAUD 115200
#endif

#if defined(TFT_WIDTH) && defined(TFT_HEIGHT)
#define TEST_TFT
#include "SPI.h"
#include "TFT_eSPI.h"
TFT_eSPI tft = TFT_eSPI();
#endif

#ifdef HW_CONTROLLER_I2C_PCF8574
#include <Wire.h>
#include "PCF8574.h"

volatile bool keyPressed = false;
ICACHE_RAM_ATTR void keyChangedOnPCF8574();

PCF8574 pcf8574(HW_CONTROLLER_I2C_PCF8574_ADDR, HW_CONTROLLER_I2C_PCF8574_INT_PIN, keyChangedOnPCF8574);
#endif

enum TestType
{
  AUTO,
  USER,
  MANUAL
};

struct TestDef
{
  String name;
  String result;
  bool userConfirmed;
  String userInquiry;
  bool passed;
  bool (*validate)();
};

#define RESULT_STARTS_AT 10

TestDef tests[] = {
#ifdef TEST_TFT
    {"TFT", "", true, "Can you see image on the screen?", false, NULL},
#endif
#ifdef HW_PIN_BUZZER
    {"BZR", "", true, "Did you hear beep?", false, NULL},
#endif
#ifdef I2C_SCAN
    {"I2C_SCAN", "", false, "", false, []()
     {
       #if defined(HW_PIN_I2C_SDA) && defined(HW_PIN_I2C_SCL)
       Wire.begin(HW_PIN_I2C_SDA, HW_PIN_I2C_SCL);
       #else
       Wire.begin();
       #endif 

       byte error, address;
       int nDevices = 0;

       delay(5000);

       Serial.println("Scanning for I2C devices ...");
       for (address = 0x01; address < 0x7f; address++)
       {
         Wire.beginTransmission(address);
         error = Wire.endTransmission();
         if (error == 0)
         {
           Serial.printf("I2C device found at address 0x%02X\n", address);
           nDevices++;
         }
         else if (error != 2)
         {
           Serial.printf("Error %d at address 0x%02X\n", error, address);
         }
       }
       if (nDevices == 0)
       {
         Serial.println("No I2C devices found");
       }
       return false;
     }},
#endif
#ifdef HW_CONTROLLER_I2C_PCF8574
    {"GPIO_I", "", false, "", false, []()
     {
       #if defined(HW_PIN_I2C_SDA) && defined(HW_PIN_I2C_SCL)
       Wire.begin(HW_PIN_I2C_SDA, HW_PIN_I2C_SCL);
       #else
       Wire.begin();
       #endif 

       pcf8574.pinMode(P0, INPUT_PULLUP);
       pcf8574.pinMode(P1, INPUT_PULLUP);
       pcf8574.pinMode(P2, INPUT_PULLUP);
       pcf8574.pinMode(P3, INPUT_PULLUP);

       pcf8574.pinMode(P4, INPUT_PULLUP);
       pcf8574.pinMode(P5, INPUT_PULLUP);
       pcf8574.pinMode(P6, INPUT_PULLUP);
       pcf8574.pinMode(P7, INPUT_PULLUP);

       Serial.print("Init pcf8574...");
       if (pcf8574.begin())
       {
         Serial.println("OK");
         return true;
       }
       else
       {
         Serial.println("FAILED");
         return false;
       }
     }},
    {"GPIO_0", "", false, "", false, []()
     {
        if (keyPressed)
        {
          uint8_t value = pcf8574.digitalRead(P0);
          if (value == LOW)
          {
            keyPressed = false;
            return true;
          }
        }

       return false;
     }},
     {"GPIO_1", "", false, "", false, []()
     {
        if (keyPressed)
        {
          uint8_t value = pcf8574.digitalRead(P1);
          if (value == LOW)
          {
            keyPressed = false;
            return true;
          }
        }

       return false;
     }},
     {"GPIO_2", "", false, "", false, []()
     {
        if (keyPressed)
        {
          uint8_t value = pcf8574.digitalRead(P2);
          if (value == LOW)
          {
            keyPressed = false;
            return true;
          }
        }

       return false;
     }},
     {"GPIO_3", "", false, "", false, []()
     {
        if (keyPressed)
        {
          uint8_t value = pcf8574.digitalRead(P3);
          if (value == LOW)
          {
            keyPressed = false;
            return true;
          }
        }

       return false;
     }},
     {"GPIO_4", "", false, "", false, []()
     {
        if (keyPressed)
        {
          uint8_t value = pcf8574.digitalRead(P4);
          if (value == LOW)
          {
            keyPressed = false;
            return true;
          }
        }

       return false;
     }},
     {"GPIO_5", "", false, "", false, []()
     {
        if (keyPressed)
        {
          uint8_t value = pcf8574.digitalRead(P5);
          if (value == LOW)
          {
            keyPressed = false;
            return true;
          }
        }

       return false;
     }},
     {"GPIO_6", "", false, "", false, []()
     {
        if (keyPressed)
        {
          uint8_t value = pcf8574.digitalRead(P6);
          if (value == LOW)
          {
            keyPressed = false;
            return true;
          }
        }

       return false;
     }},
     {"GPIO_7", "", false, "", false, []()
     {
        if (keyPressed)
        {
          uint8_t value = pcf8574.digitalRead(P7);
          if (value == LOW)
          {
            keyPressed = false;
            return true;
          }
        }

       return false;
     }},
#endif
#ifdef BOARD_HAS_PSRAM
    {"PSRAM", "", false, "", false, []()
     {
       Serial.printf("PSRAM: %d\n", ESP.getFreePsram());
       char *tmp = (char *)ps_malloc(1024);
       return (tmp != 0);
     }},
#endif
};

#define tests_count (sizeof(tests) / sizeof(*tests))

#ifdef TEST_TFT
unsigned long testText()
{
  tft.fillScreen(TFT_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(TFT_YELLOW);
  tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  // tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}
#endif

#ifdef HW_PIN_BUZZER
void testBuzzer()
{
  tone(HW_PIN_BUZZER, 1024, 256);
}
#endif

#ifdef HW_CONTROLLER_I2C_PCF8574
void keyChangedOnPCF8574()
{
  keyPressed = true;
}
#endif

void setup()
{

  Serial.begin(SERIAL_BAUD);

  while (!Serial)
    ;
  delay(1000);

#ifdef TEST_TFT
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setViewport(0, 0, TFT_WIDTH, TFT_HEIGHT);
#ifdef TFT_ROTATION
  tft.setRotation(TFT_ROTATION);
#endif
#endif

#ifdef TEST_TFT
  Serial.println(F("Testing TFT ... "));
  testText();
#endif

#ifdef HW_PIN_BUZZER
  testBuzzer();
#endif

  Serial.println("\n\nESP development boards hw test ..");

  for (uint8_t i = 0; i < tests_count; i++)
  {
    auto test = tests[i];
    if (!test.passed)
    {
      if (test.userConfirmed)
      {
        Serial.printf("[%s] %s\n", test.name, test.userInquiry.c_str());
        bool hasAnswer = false;
        while (!hasAnswer)
        {
          while (!Serial.available())
          {
            // Serial.print(".");
            delay(10);
          }
          uint8_t c = Serial.read();

          Serial.print("<-");
          Serial.println(c);

          if ((c == 89) || (c == 121))
          {
            tests[i].passed = true;
            hasAnswer = true;
          }
          else if ((c == 78) || (c == 110))
          {
            tests[i].passed = false;
            hasAnswer = true;
          }
        }
      }
    }
  }
}

void loop(void)
{

#ifdef TEST_TFT
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
#endif

  // validate auto tests
  for (uint8_t i = 0; i < tests_count; i++)
  {
    auto test = tests[i];
    if (!test.passed)
    {
      if (!test.userConfirmed)
      {
        Serial.printf("Starting %s\n", test.name);
        tests[i].passed = test.validate();
      }
    }
  }

  // indicate status
  for (uint8_t i = 0; i < tests_count; i++)
  {
    auto test = tests[i];

#ifdef TEST_TFT
    tft.setTextColor(TFT_WHITE);
    tft.printf("[%s] ", test.name.c_str());
    for (uint8_t x = 0; x < RESULT_STARTS_AT - test.name.length() - 2; x++)
      tft.print(' ');
    if (test.passed)
    {
      tft.setTextColor(TFT_GREEN);
      tft.println("PASS");
    }
    else
    {
      tft.setTextColor(TFT_RED);
      tft.println("FAIL");
    }
#else
    Serial.printf("[%s] ", test.name.c_str());
    for (uint8_t x = 0; x < RESULT_STARTS_AT - test.name.length() - 2; x++)
      Serial.print(' ');
    if (test.passed)
    {
      Serial.println("PASS");
    }
    else
    {
      Serial.println("FAIL");
    }

#endif
  }

#if defined(TEST_JOYSTICK) && defined(TEST_TFT)
  uint32_t x = (analogRead(TEST_JOYSTICK_A) >> 4);
  uint32_t y = (analogRead(TEST_JOYSTICK_B) >> 4);

  tft.setTextColor(TFT_BLUE);
  tft.setCursor(x, y);
  tft.print('X');
#endif

  Serial.println("\n\n");

  delay(1000);
}
