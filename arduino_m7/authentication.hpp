#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <RPC.h>

namespace Authentication {

  uint32_t authentication_array = 0;

  void displayArray(uint32_t array) {
    for (uint8_t i = 0; i < 16; i++) {
      uint32_t shifted_array = array >> (2*i);
      uint8_t display_value = shifted_array & 0x3;
      RPC.call("setEyePixelDirect", i, display_value);
    }
  }

  void initiateAuthentication() {
    // authentication_array = random(0xFFFFFFFF);
    authentication_array = 0x1 << 2; /* EXPERIMENTAL */ // Array is always only 1 in first cell
    displayArray(authentication_array);
  }

  uint8_t authenticateUser(uint32_t array) {
    uint8_t is_valid = authentication_array == array;
    if (is_valid) changeRobotState(RobotState::Running);
    return is_valid;
  }

}
