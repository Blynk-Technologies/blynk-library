/*
 * Copyright (c) 2026 Blynk Technologies Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Project-specific Interaction: maps Edgent states to LED modes,
 * implements button hold behavior (config reset).
 */

#pragma once

#include "BoardConfig.h"
#include <indicator/IndicatorBase.h>

#if defined(BOARD_LED_PIN_RGB)
  #include <indicator/LedSmart.h>
  #define BOARD_LED_CLASS LedSmart
#elif defined(BOARD_LED_PIN_R)
  #include <indicator/LedRgbPwm.h>
  #define BOARD_LED_CLASS LedRgbPwm
#elif defined(BOARD_LED_PIN)
  #include <indicator/LedMono.h>
  #define BOARD_LED_CLASS LedMono
#endif

#ifdef BOARD_LED_CLASS

class BlynkIndicator : public IndicatorBase<BOARD_LED_CLASS> {
public:
  using Base = IndicatorBase<BOARD_LED_CLASS>;
  using Base::Base;  // Inherit LedDriver constructors

  enum Mode {
    STAY_OFF,
    BLINK_YELLOW_SLOW,
    BLINK_BLUE_SLOW,
    BLINK_BLUE_FAST,
    BLINK_GREEN_SLOW,
    BLINK_GREEN_FAST,
    WAVE_BLYNK_SLOW,
    WAVE_MAGENTA_SLOW,
    BLINK_WHITE_FAST,
    BLINK_WHITE_XFAST,
    WAVE_WHITE_FAST,
    BLINK_MAGENTA_FAST,
    HEARTBEAT_RED
  };

  void setMode(Mode m) {
    Base::setMode((int)m);
  }

protected:

  uint32_t run() override {
    if (_modePrev != _mode) {
      _modePrev = _mode;
      _counter = 0;
      if (_mode == STAY_OFF) {
        off();
      }
    }

    switch (_mode) {
    case STAY_OFF:              return skipLED();
    case BLINK_YELLOW_SLOW:     return beatLED(COLOR_YELLOW,  (int[]){ 50, 2000 });
    case BLINK_BLUE_SLOW:       return beatLED(COLOR_BLUE,    (int[]){ 50, 500 });
    case BLINK_BLUE_FAST:       return beatLED(COLOR_BLUE,    (int[]){ 200, 200 });
    case BLINK_GREEN_SLOW:      return beatLED(COLOR_GREEN,   (int[]){ 50, 500 });
    case BLINK_GREEN_FAST:      return beatLED(COLOR_GREEN,   (int[]){ 100, 100 });
    case WAVE_BLYNK_SLOW:       return waveLED(COLOR_BLYNK,   5000);
    case WAVE_MAGENTA_SLOW:     return waveLED(COLOR_MAGENTA, 5000);
    case BLINK_WHITE_FAST:      return beatLED(COLOR_WHITE,   (int[]){ 50, 200 });
    case BLINK_WHITE_XFAST:     return beatLED(COLOR_WHITE,   (int[]){ 50, 50 });
    case WAVE_WHITE_FAST:       return waveLED(COLOR_WHITE,   1000);
    case BLINK_MAGENTA_FAST:    return beatLED(COLOR_MAGENTA, (int[]){ 50, 50 });
    case HEARTBEAT_RED:         return beatLED(COLOR_RED,     (int[]){ 80, 100, 80, 1000 } );
    default:                    return skipLED();
    }
  }
};

#endif

#if defined(BOARD_BUTTON_PIN)
#include <OneButton.h>
#endif

class BlynkInteraction {
public:

  // LED configured with board-specific parameters
#if defined(BOARD_LED_PIN_RGB)
  BlynkIndicator led { BOARD_LED_PIN_RGB, BOARD_LED_TYPE };
#elif defined(BOARD_LED_PIN_R)
  BlynkIndicator led { BOARD_LED_PIN_R, BOARD_LED_PIN_G, BOARD_LED_PIN_B, BOARD_LED_INVERSE, BOARD_PWM_RANGE };
#elif defined(BOARD_LED_PIN)
  BlynkIndicator led { BOARD_LED_PIN, BOARD_LED_INVERSE, BOARD_PWM_RANGE };
#endif

#if defined(BOARD_BUTTON_PIN)
  OneButton btn { BOARD_BUTTON_PIN, BOARD_BUTTON_ACTIVE_LOW };
#endif

  void begin() {
    _instance = this;

#if defined(BOARD_LED_CLASS)
    led.setBrightness(BOARD_LED_BRIGHTNESS, BOARD_LED_MIN_BRIGHTNESS);
    led.begin();
#endif

#if defined(BOARD_BUTTON_PIN)
    btn.setPressMs(BUTTON_HOLD_TIME_LONG_PRESS);
    btn.setLongPressIntervalMs(1000);

    btn.attachLongPressStart([]() {
      BLYNK_LOG("Button: Long Press!");
    });
    btn.attachDuringLongPress([]() {
      uint32_t passed = _instance->btn.getPressedMs();
      if (passed > BUTTON_HOLD_TIME_CANCEL) {
        if (_instance->_willReset) {
          _instance->_willReset = false;
          _instance->updateIndicator();
          BLYNK_LOG("Config reset canceled");
        }
      } else if (passed > BUTTON_HOLD_TIME_CONFIG_RESET) {
        if (!_instance->_willReset) {
          _instance->_willReset = true;
#if defined(BOARD_LED_CLASS)
          _instance->led.setMode(BlynkIndicator::BLINK_WHITE_FAST);
#endif
          BLYNK_LOG("Release the button to reset config!");
        }
      } else if (passed > BUTTON_HOLD_TIME_INDICATION) {
#if defined(BOARD_LED_CLASS)
        _instance->led.setMode(BlynkIndicator::WAVE_WHITE_FAST);
#endif
      }
    });
    btn.attachLongPressStop([]() {
      uint32_t passed = _instance->btn.getPressedMs();
      if (passed > BUTTON_HOLD_TIME_CANCEL) {
        // Button was held for too long -> cancel
      } else if (passed > BUTTON_HOLD_TIME_CONFIG_RESET) {
        BLYNK_LOG("Resetting configuration");
        BlynkEdgent.resetConfig();
      } else {
        BLYNK_LOG("Button: Released (%lu ms)", (long unsigned)passed);
      }
      _instance->_willReset = false;
      _instance->updateIndicator();
    });

    btn.attachClick([](){
      BLYNK_LOG("Button: Click!");
    });
    btn.attachDoubleClick([](){
      BLYNK_LOG("Button: Double Click!");
    });
#endif
  }

  void run() {
#if defined(BOARD_BUTTON_PIN)
    btn.tick();
#endif
  }

  void updateIndicator() {
#if defined(BOARD_LED_CLASS)
    switch (BlynkEdgent.getState()) {
    case Edgent::MODE_IDLE:             led.setMode(BlynkIndicator::BLINK_YELLOW_SLOW);  break;
    case Edgent::MODE_WAIT_CONFIG:      led.setMode(BlynkIndicator::BLINK_BLUE_SLOW);    break;
    case Edgent::MODE_CONNECTING_NET:
    case Edgent::MODE_CONNECTING_CLOUD: led.setMode(BlynkIndicator::BLINK_GREEN_SLOW);   break;
    case Edgent::MODE_RUNNING:          led.setMode(BlynkIndicator::WAVE_BLYNK_SLOW);    break;
    case Edgent::MODE_OTA_UPGRADE:      led.setMode(BlynkIndicator::WAVE_MAGENTA_SLOW);  break;
    case Edgent::MODE_ERROR:            led.setMode(BlynkIndicator::HEARTBEAT_RED);      break;
    default:                            led.setMode(BlynkIndicator::STAY_OFF);           break;
    }
#endif
  }

private:
  bool _willReset;
  static BlynkInteraction* _instance;
};

BlynkInteraction* BlynkInteraction::_instance = nullptr;

BlynkInteraction interaction;
