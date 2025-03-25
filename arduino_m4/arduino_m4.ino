#include <RPC.h>

#include "servos.hpp"
#include "driving.hpp"

RobotServos servos{};
RobotDriving driving {};

void setup() {
  RPC.begin();
  RPC.println("M4: Booted up M4");
  servos.init();
  driving.init();
}

void loop() {
  servos.turnHead(255);
  delay(1000);
  servos.turnHead(0);
  delay(1000);
  servos.tiltHead(255);
  delay(1000);
  servos.tiltHead(0);
  delay(1000);
  servos.moveLeftArm(255);
  delay(1000);
  servos.moveLeftArm(0);
  delay(1000);
  servos.moveLeftHand(255);
  delay(1000);
  servos.moveLeftHand(0);
  delay(1000);
  servos.moveRightArm(255);
  delay(1000);
  servos.moveRightArm(0);
  delay(1000);
  servos.moveRightHand(255);
  delay(1000);
  servos.moveRightHand(0);
  delay(1000);
}
