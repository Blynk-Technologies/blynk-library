/******************************************************************************
 * 1. In the Arduino IDE, select:
 *    Tools -> Board -> Select your board
 *    Tools -> Port  -> Select your port
 *    Tools -> Flash Size -> At least 128 KB FS
 *
 * 2. In BoardConfig.h, configure the LED and button pins.
 *    Or, select a predefined configuration at the top of this sketch, e.g.:
 *    #define ARDUINO_ESP8266_WITTY
 *
 * 3. Fill in TEMPLATE_ID and TEMPLATE_NAME from your Blynk Template below.
 *    Read more: https://bit.ly/BlynkInject
 *
 * 4. Install the required libraries:
 *    http://librarymanager#Preferences          v2.4.0
 *    http://librarymanager#ArduinoJson          v7.4.3
 *    http://librarymanager#ArduinoHttpClient    v0.6.2
 *    http://librarymanager#OneButton            v2.6.2
 *    http://librarymanager#Adafruit%20NeoPixel  v1.15.5
 *
 * 5. Upload the sketch to your board and open the Serial Monitor at 115200 baud.
 *
 * 6. Use the Blynk IoT App to provision your device:
 *    Menu -> Add new device -> Find devices nearby -> Select your device
 *
 *****************************************************************************/

//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"

/* White labeling (use this ONLY if you have a branded Blynk App) */
//#define BLYNK_VENDOR_PREFIX         "Blynk"
//#define BLYNK_DEFAULT_SERVER        "my-dashboard.com"

/* The firmware version (used for OTA updates) */
#define BLYNK_FIRMWARE_VERSION      "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#include <Arduino.h>
#include <BlynkEdgent.h>
#include "Interaction.h"

void setup()
{
  Serial.begin(115200);
  delay(1000);  // Wait for serial monitor (remove if not needed)
  Serial.println();

  // The amount of time (in seconds) to wait for the user to configure the device.
  // If configuration is skipped, the device will enter IDLE mode. Default: 10 min
  BlynkEdgent.setConfigTimeout(10*60);

  // The amount of times the board enters the config mode automatically.
  // NOTE: 0 means unlimited, and is only useful for testing. Default: 10
  BlynkEdgent.setConfigSkipLimit(0);

  // Edgent state indication and button interaction
  interaction.begin();
  BlynkEdgent.onStateChange([](){
    BLYNK_LOG("State: %s", BlynkEdgent.getStateName());
    interaction.updateIndicator();
  });

  // Initialize Blynk.Edgent
  BlynkEdgent.begin();

  // Attach Blynk console to the Serial
  BlynkEdgent.initConsole(BLYNK_PRINT);
}

void loop()
{
  BlynkEdgent.run();
  interaction.run();
  delay(1);
}
