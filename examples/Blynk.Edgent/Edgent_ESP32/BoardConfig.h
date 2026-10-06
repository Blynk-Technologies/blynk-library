/*
 * Copyright (c) 2026 Blynk Technologies Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

/*
 * Board configuration (see examples below).
 *
 * The board macro is defined by PlatformIO, based on the `board` option
 * of the selected environment in platformio.ini.
 */

#if defined(ARDUINO_ESP32_DEV)

  // Generic ESP32 dev board (esp32dev)
  #define BOARD_BUTTON_PIN            0     // BOOT button
  #define BOARD_BUTTON_ACTIVE_LOW     true

  // Most (but not all) ESP32 dev boards have an LED on gpio2
  #define BOARD_LED_PIN               2
  #define BOARD_LED_INVERSE           false
  #define BOARD_LED_BRIGHTNESS        64

#elif defined(ARDUINO_ESP32C3_DEV)

  // ESP32-C3-DevKitM-1 (esp32-c3-devkitm-1)
  #define BOARD_BUTTON_PIN            9
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN_RGB           8
  #define BOARD_LED_BRIGHTNESS        32

#elif defined(ARDUINO_ESP32S2_DEV)

  // ESP32-S2-Saola-1 (esp32-s2-saola-1)
  #define BOARD_BUTTON_PIN            0
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN_RGB           18
  #define BOARD_LED_BRIGHTNESS        32

#elif defined(ARDUINO_ESP32S3_DEV)

  // ESP32-S3-DevKitC-1 (esp32-s3-devkitc-1)
  // NOTE: on board revision v1.1 the RGB LED is connected to gpio38
  #define BOARD_BUTTON_PIN            0
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN_RGB           48
  #define BOARD_LED_BRIGHTNESS        32

#elif defined(ARDUINO_ESP32C2_DEV)

  // ESP8684-DevKitM-1 (esp32-c2-devkitm-1)
  #define BOARD_BUTTON_PIN            9
  #define BOARD_BUTTON_ACTIVE_LOW     true

  // NOTE: NeoPixel issue https://github.com/adafruit/Adafruit_NeoPixel/issues/450
  #define BOARD_LED_PIN               8
  #define BOARD_LED_BRIGHTNESS        64

#elif defined(ARDUINO_ESP32C5_DEV)

  // ESP32-C5-DevKitC-1 (esp32-c5-devkitc-1)
  #define BOARD_BUTTON_PIN            28
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN_RGB           27
  #define BOARD_LED_BRIGHTNESS        32

#elif defined(ARDUINO_ESP32C6_DEV)

  // ESP32-C6-DevKitC-1 (esp32-c6-devkitc-1)
  #define BOARD_BUTTON_PIN            9
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN_RGB           8
  #define BOARD_LED_BRIGHTNESS        32

#elif defined(ARDUINO_WROVER_BOARD)

  #define BOARD_BUTTON_PIN            15
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN_R             0
  #define BOARD_LED_PIN_G             2
  #define BOARD_LED_PIN_B             4
  #define BOARD_LED_INVERSE           false
  #define BOARD_LED_BRIGHTNESS        128

#elif defined(ARDUINO_TTGO_T7)

  // This board does not have a built-in button
  // Connect a button to gpio0 <> GND
  #define BOARD_BUTTON_PIN            0
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN               19
  #define BOARD_LED_INVERSE           false
  #define BOARD_LED_BRIGHTNESS        64

#elif defined(ARDUINO_TTGO_T7_S3)

  #define BOARD_BUTTON_PIN            0
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN               17
  #define BOARD_LED_INVERSE           false
  #define BOARD_LED_BRIGHTNESS        64

#elif defined(ARDUINO_XIAO_ESP32C5)

  #define BOARD_BUTTON_PIN            28
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN               27
  #define BOARD_LED_INVERSE           true
  #define BOARD_LED_BRIGHTNESS        64

#elif defined(ARDUINO_WEACT_ESP32C5)

  #define BOARD_BUTTON_PIN            28
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN_RGB           27
  #define BOARD_LED_BRIGHTNESS        64

#elif defined(ARDUINO_TTGO_TETH_POE)

  // This board does not have a built-in button
  // Connect a button to gpio0 <> GND
  #define BOARD_BUTTON_PIN            0
  #define BOARD_BUTTON_ACTIVE_LOW     true

  // This board does not have a built-in indicator
  #define BOARD_LED_PIN               2

#elif defined(ARDUINO_TTGO_TCALL_SIM800) || defined(ARDUINO_TTGO_TPCIE)

  // This board does not have a built-in button
  // Connect a button to gpio0 <> GND
  #define BOARD_BUTTON_PIN            0
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN               LED_GPIO
  #define BOARD_LED_INVERSE           LED_INVERSE
  #define BOARD_LED_BRIGHTNESS        64

#elif defined(ARDUINO_TTGO_T_OI)

  // This board does not have a built-in button
  // Connect a button to gpio6 <> GND
  #define BOARD_BUTTON_PIN            6
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN               3
  #define BOARD_LED_INVERSE           false
  #define BOARD_LED_BRIGHTNESS        64

#elif defined(ARDUINO_ESP32C3_DEV_MODULE)

  #define BOARD_BUTTON_PIN            9
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN_RGB           8
  #define BOARD_LED_INVERSE           false
  #define BOARD_LED_BRIGHTNESS        32

#elif defined(ARDUINO_ESP32S2_DEV_KIT)

  #define BOARD_BUTTON_PIN            0
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN               19
  #define BOARD_LED_INVERSE           false
  #define BOARD_LED_BRIGHTNESS        128

#elif defined(ARDUINO_WILOBE) || defined(ARDUINO_WILOBE_V2)

  #define BOARD_BUTTON_PIN            35
  #define BOARD_BUTTON_ACTIVE_LOW     true
  #define BOARD_LED_PIN               2

#elif defined(ARDUINO_EDGEBOX_ESP100)

  #define BOARD_BUTTON_PIN            0
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN               LED_ACT
  #define BOARD_LED_INVERSE           true
  #define BOARD_LED_BRIGHTNESS        255

#elif defined(ARDUINO_UBLOX_NINA_W10)

  #define BOARD_LED_PIN_R             27                    // Set R,G,B pins - if your LED is PWM RGB
  #define BOARD_LED_PIN_G             25
  #define BOARD_LED_PIN_B             26
  #define BOARD_LED_INVERSE           true                  // true if LED is common anode, false if common cathode
  #define BOARD_LED_BRIGHTNESS        64                    // 0..255 brightness control

#else

  #warning "Custom board configuration is used"

  #define BOARD_BUTTON_PIN            0                     // Pin where user button is attached
  #define BOARD_BUTTON_ACTIVE_LOW     true                  // true if button is "active-low"

  //#define BOARD_LED_PIN             2                     // Set LED pin - if you have a single-color LED attached
  //#define BOARD_LED_PIN_R           15                    // Set R,G,B pins - if your LED is PWM RGB
  //#define BOARD_LED_PIN_G           12
  //#define BOARD_LED_PIN_B           13
  //#define BOARD_LED_PIN_RGB         4                     // Set if your LED is an addressable RGB
  //#define BOARD_LED_TYPE            NEO_GRB + NEO_KHZ800  // Set if your LED is an addressable RGB
  #define BOARD_LED_INVERSE           false                 // true if LED is common anode, false if common cathode
  #define BOARD_LED_BRIGHTNESS        64                    // 0..255 brightness control

#endif

#define BUTTON_HOLD_TIME_LONG_PRESS    1000
#define BUTTON_HOLD_TIME_INDICATION    4000
#define BUTTON_HOLD_TIME_CONFIG_RESET  10000
#define BUTTON_HOLD_TIME_CANCEL        20000

#if !defined(BOARD_PWM_RANGE)
#define BOARD_PWM_RANGE                256
#endif

#if !defined(BOARD_LED_MIN_BRIGHTNESS)
#define BOARD_LED_MIN_BRIGHTNESS       4
#endif

#if !defined(BOARD_LED_INVERSE)
#define BOARD_LED_INVERSE              false
#endif

#if !defined(BOARD_LED_TYPE)
#define BOARD_LED_TYPE                 NEO_GRB + NEO_KHZ800
#endif
