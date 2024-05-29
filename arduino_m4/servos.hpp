#include <stdint.h>
#include <Arduino.h>
#include <RPC.h>
#include <Servo.h>

namespace Servos {

  Servo TURN_HEAD;
  Servo TILT_HEAD;
  Servo ARM_LEFT;
  Servo HAND_LEFT;
  Servo ARM_RIGHT;
  Servo HAND_RIGHT;
 
  void init() {
    TURN_HEAD.attach(SERVO_TURN_HEAD_PIN);
    TILT_HEAD.attach(SERVO_TILT_HEAD_PIN);
    ARM_LEFT.attach(SERVO_ARM_LEFT_PIN);
    HAND_LEFT.attach(SERVO_HAND_LEFT_PIN);
    ARM_RIGHT.attach(SERVO_ARM_RIGHT_PIN);
    HAND_RIGHT.attach(SERVO_HAND_RIGHT_PIN);
    RPC.println("Servos initialized.");
  }

  /**
   * servo: one of the robots servos (e.g. TURN_HEAD)
   * position: 0 (left maximum) to 180 (right maximum)
   */
  void write(Servo &servo, uint8_t position) {
    servo.write(position);
  }

}
