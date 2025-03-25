#include "eyes.hpp"
#include <RPC.h>

RobotEyes::RobotEyes() :
  pixels{pixel_count, pixel_pin, NEO_GRB + NEO_KHZ800} {}

bool RobotEyes::init() {
  pixels.begin();
  Serial.println("Eyes initialized");
  return true;
}

void RobotEyes::showEyesArray(EyePixel eye_pixels[pixel_count]) {
  for (int i = 0; i < pixel_count; i++) {
    pixels.setPixelColor(i, pixels.Color(eye_pixels[i].red, eye_pixels[i].green, eye_pixels[i].blue));
  }
  pixels.show();
}