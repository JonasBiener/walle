#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <RPC.h>

namespace Authentication {

  uint32_t createArray() {
    // uint32_t random_number = random(0xFFFFFFFF);
    // return random_number;
    return 0x1 << 2; /* EXPERIMENTAL */ // Array is always only 1 in first cell
  }

  uint8_t validateArray(uint32_t original, uint32_t compare) {
    return original == compare;
  }

  void displayArray(uint8_t* display, uint32_t array) {
    for (uint8_t i = 0; i < 16; i++) {
      uint32_t shifted_array = array >> (2*i);
      uint8_t display_value = shifted_array & 0x3;
      display[i] = display_value;
    }
  }


}