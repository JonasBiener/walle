#ifndef ROBOT_DRIVING_HPP
#define ROBOT_DRIVING_HPP

#include <Arduino.h>
#include <Adafruit_MotorShield.h>

class RobotDriving {

  public:

    RobotDriving();

    /*  
      Initializes the motor shield
    */
    bool init();

    /*  
      Rotates a motor using the motor shield
      speed: -255 (reverse) to 255 (forward)
    */
    void rotate(Adafruit_DCMotor* motor, int speed);

    /*  
      Controls the robots' driving
      direction: -255 (left) to 255 (right)
      speed -255 (reverse) to 255 (forward)
    */
    void drive(int direction, int speed);

  private:

    // CONSTANTS //
    // Address of the Adafruit-Motor-Shield
    const int motor_shield_address = 0x61;
    // Ports of the motors on the Adafruit-Motor-Shield
    const int left_motor_port = 3;
    const int right_motor_port = 4;
    // Minimum values for movement
    const int minumum_speed_absolute = 40;
    const int minimun_direction_absolute = 40;

    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor* left_motor;
    Adafruit_DCMotor* right_motor;

};

#endif