#include "servos.hpp"
#include <RPC.h>

RobotServos::RestrictedServo::RestrictedServo(int pin, int min_pos, int max_pos, bool inv) :
  servo_pin{pin},
  min_position{min_pos},
  max_position{max_pos},
  inverted{inv} {}

bool RobotServos::RestrictedServo::init() {
  servo.attach(servo_pin);
  return true;
}

void RobotServos::RestrictedServo::move(int position) {
  float calculated_position = (position / 255.0) * (max_position - min_position);
  if (inverted) calculated_position = max_position - calculated_position;
  else calculated_position = calculated_position + min_position;
  servo.write(static_cast<int>(calculated_position));
}

bool RobotServos::init() {
  turn_head.init();
  tilt_head.init();
  arm_left.init();
  // hand_left.init();
  arm_right.init();
  hand_right.init();
  turn_head.move(0);
  tilt_head.move(0);
  arm_left.move(0);
  // hand_left.move(0);
  arm_right.move(0);
  hand_right.move(0);
  Serial.println("Servos initialized");
  return true;
}

void RobotServos::turnHead(int position) {
  turn_head.move(position);
}

void RobotServos::tiltHead(int position) {
  tilt_head.move(position);
}

void RobotServos::moveLeftArm(int position) {
  arm_left.move(position);
}

void RobotServos::moveLeftHand(int position) {
  // hand_left.move(position);
}

void RobotServos::moveRightArm(int position) {
  arm_right.move(position);
}

void RobotServos::moveRightHand(int position) {
  hand_right.move(position);
}

