#include <stdint.h>
#include <Arduino.h>
#include <RPC.h>
#include <wiring_private.h>
#include <Adafruit_MotorShield.h>

namespace Motors {

  const uint8_t LEFT = 1;
  const uint8_t RIGHT = 2;

  Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
  Adafruit_DCMotor *left_motor = AFMS.getMotor(LEFT_MOTOR_PORT);
  Adafruit_DCMotor *right_motor = AFMS.getMotor(RIGHT_MOTOR_PORT);

  void init() {
    if (!AFMS.begin()) {
      RPC.println("ERR: Could not find Motor Shield. Check wiring.");
      return;
    } 
    RPC.println("Motor-Shield initialized.");
  }

  /**
   * motor: LEFT (left motor) or RIGHT (right motor)
   * speed: -225 (reverse) to 255 (forward)
   */
  void rotate(uint8_t motor, int16_t speed) {
    if (motor == LEFT) {
      left_motor->setSpeed(abs(speed));
      if (speed > 0) left_motor->run(FORWARD);
      else if (speed < 0) left_motor->run(BACKWARD);
      else left_motor->run(RELEASE);
    }
    else if (motor == RIGHT){
      right_motor->setSpeed(abs(speed));
      if (speed > 0) right_motor->run(BACKWARD);
      else if (speed < 0) right_motor->run(FORWARD);
      else right_motor->run(RELEASE);
    }
  }
  /**
   * direction: -255 (left) to 255 (right)
   * speed: -225 (reverse) to 255 (forward)
   */
  void drive(int16_t direction, int16_t speed) {
    int16_t speed_left = 0;
    int16_t speed_right = 0;
    if (((speed > 0 && speed > MINIMUM_SPEED_ABS) || (speed < 0 && speed < -MINIMUM_SPEED_ABS)) || ((direction > 0 && direction > MINIMUM_DIRECTION_ABS) || (direction < 0 && direction < -MINIMUM_DIRECTION_ABS))) {
      speed_left = direction > 0 ? abs(direction) : -abs(direction);
      speed_right = direction < 0 ? abs(direction) : -abs(direction);
      speed_left = max(min(speed_left + speed, 255),-255);
      speed_right = max(min(speed_right + speed, 255),-255);
    }
    rotate(LEFT, speed_left);
    rotate(RIGHT, speed_right);
  }

}
