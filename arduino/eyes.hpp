#ifndef ROBOT_EYES_HPP
#define ROBOT_EYES_HPP

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class RobotEyes {

  public:

    RobotEyes();

    /*  
      Initializes the motor shield
    */
    bool init();

    void showDefault();
    void showDisabled();
    void showPaused();

  private:

    // CONSTANTS //
    // Count of neopixels in series
    static const int pixel_count = 10;
    // Pin on which neopixels are attached
    static const int pixel_pin = 1;

    struct EyePixel {
      int red = 0;
      int green = 0;
      int blue = 0;
    };

    void showEyesArray(EyePixel eye_pixels[pixel_count]);

    Adafruit_NeoPixel pixels;

};

#endif