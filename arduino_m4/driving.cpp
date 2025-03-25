#include "driving.hpp"
#include <RPC.h>

RobotDriving::RobotDriving() :
  AFMS{motor_shield_address},
  left_motor{AFMS.getMotor(left_motor_port)},
  right_motor{AFMS.getMotor(right_motor_port)} {}

bool RobotDriving::init() {
  if (!AFMS.begin()) {
    RPC.println("ERROR: Could not find Motor Shield");
    return false;
  } 
  RPC.println("Motor-Shield initialized");
  return true;
}

void RobotDriving::rotate(Adafruit_DCMotor* motor, int speed) {
  motor->setSpeed(abs(speed));
  if (speed > 0) motor->run(FORWARD);
  else if (speed < 0) motor->run(BACKWARD);
  else motor->run(RELEASE);
}

void RobotDriving::drive(int direction, int speed) {
  int speed_left = 0;
  int speed_right = 0;
  if (((speed > minumum_speed_absolute) || (speed < -minumum_speed_absolute)) || 
  ((direction > minimun_direction_absolute) || (direction < -minimun_direction_absolute))) {
    speed_left = direction > 0 ? abs(direction) : -abs(direction);
    speed_right = direction < 0 ? abs(direction) : -abs(direction);
    speed_left = max(min(speed_left + speed, 255), -255);
    speed_right = max(min(speed_right + speed, 255), -255);
  }
  rotate(left_motor, speed_left);
  rotate(right_motor, speed_right);
}