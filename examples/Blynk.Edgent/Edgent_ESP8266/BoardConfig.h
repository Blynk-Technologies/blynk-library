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

#if defined(ARDUINO_ESP8266_WEMOS_D1MINI)

  // WeMos D1 mini (d1_mini)
  // This board does not have a built-in button
  // Connect a button to gpio0 <> GND
  #define BOARD_BUTTON_PIN            0
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN               2
  #define BOARD_LED_INVERSE           true
  #define BOARD_LED_BRIGHTNESS        255

#elif defined(ARDUINO_ESP8266_NODEMCU_ESP12E)

  // NodeMCU 1.0 (nodemcuv2)
  #define BOARD_BUTTON_PIN            0     // FLASH button
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN               2
  #define BOARD_LED_INVERSE           true
  #define BOARD_LED_BRIGHTNESS        255

#elif defined(ARDUINO_ESP8266_WITTY)

  #define BOARD_BUTTON_PIN            4
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN_R             15
  #define BOARD_LED_PIN_G             12
  #define BOARD_LED_PIN_B             13
  #define BOARD_LED_INVERSE           false
  #define BOARD_LED_BRIGHTNESS        160
  #define BOARD_LED_MIN_BRIGHTNESS    52

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
