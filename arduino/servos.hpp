#ifndef ROBOT_WEBSOCKET_HPP
#define ROBOT_WEBSOCKET_HPP

#include <stdint.h>
#include <Arduino.h>
#include <RPC.h>
#include <Servo.h>

namespace Servos {

  const int servo_turn_head_pin = 2;
  const int servo_tilt_head_pin = 1;
  const int servo_arm_left_pin = 0;
  const int servo_hand_left_pin = 3;
  const int servo_arm_right_pin = 5;
  const int servo_hand_right_pin = 4;

  Servo turn_head;
  Servo tilt_head;
  Servo arm_left;
  Servo hand_left;
  Servo arm_right;
  Servo hand_right;
 
  void init() {
    turn_head.attach(servo_turn_head_pin);
    tilt_head.attach(servo_tilt_head_pin);
    arm_left.attach(servo_arm_left_pin);
    hand_left.attach(servo_hand_left_pin);
    arm_right.attach(servo_arm_right_pin);
    hand_right.attach(servo_hand_right_pin);
    RPC.println("Servos initialized.");
  }

  /**
   * servo: one of the robots servos (e.g. turn_hea)
   * position: 0 (left maximum) to 180 (right maximum)
   */
  void write(Servo &servo, uint8_t position) {
    servo.write(position);
  }

}

#endif