#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <RPC.h>

namespace Eyes {

  enum class EyeState : uint8_t { 
    Off, GreenSlow, GreenFast, GreenSolid, RedSlow, RedFast, RedSolid 
  };

  EyeState eye_state = EyeState::Off;

  void init() {
    pinMode(EYE_GREEN_PIN, OUTPUT);
    pinMode(EYE_RED_PIN, OUTPUT);
    analogWrite(EYE_GREEN_PIN, 0);
    analogWrite(EYE_RED_PIN, 0);
    RPC.println("Eyes initialized.");
  }

  void setState(EyeState state) {
    eye_state = state;
  }

  void update() {
    uint8_t red_value = 0;
    uint8_t green_value = 0;
    switch (eye_state) {
      case EyeState::Off:
        red_value = 0;
        green_value = 0;
        break;
      case EyeState::GreenSlow:
        red_value = 0;
        green_value = 255.0 * abs(sin(2.0*PI*millis()/5000));;
        break;
      case EyeState::GreenFast:
        red_value = 0;
        green_value = 255.0 * sin(2.0*PI*millis()/250);
        break;
      case EyeState::GreenSolid:
        red_value = 0;
        green_value = 255;
        break;
      case EyeState::RedSlow:
        red_value = 255.0 * abs(sin(2.0*PI*millis()/5000));;
        green_value = 0;
        break;
      case EyeState::RedFast:
        red_value = 255.0 * sin(2.0*PI*millis()/250);
        green_value = 0;
        break;
      case EyeState::RedSolid:
        red_value = 255;
        green_value = 0;
        break;
    }
    analogWrite(EYE_RED_PIN, red_value);
    analogWrite(EYE_GREEN_PIN, green_value);
  }

}
