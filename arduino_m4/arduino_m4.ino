#include "F:/GitHub/walle/arduino_common/definitions.hpp" // Change according to source-path

#include <RPC.h>

#include "servos.hpp" 
#include "motors.hpp" 
#include "eyes.hpp" 

BLEState ble_state = BLEState::Advertising;
RobotState robot_state = RobotState::Disconnected;

int16_t cur_drive_speed = 0;
int16_t cur_drive_direction = 0;

void setup() {
  RPC.begin();
  RPC.bind("setRobotValue", setRobotValue);
  RPC.bind("setEyePixelDirect", Eyes::setPixelDirect);
  pinMode(BLE_STATUS_LED_PIN, OUTPUT);
  digitalWrite(BLE_STATUS_LED_PIN, 0);
  pinMode(BLE_PAIR_BUTTON_PIN, INPUT_PULLUP);
  Servos::init();
  Motors::init();
  Eyes::init();
  Eyes::setState(Eyes::EyeState::RedSolid);
}

void loop() { 
  runBLEDisconnectButtonThread();
  runBLEStatusLEDThread();
  Eyes::update();
}

void setRobotValue(uint8_t robot_value, int16_t data) {
  switch ((RobotValue) robot_value) {
    case RobotValue::BLEState:
      ble_state = (BLEState) data;  
      RPC.print("BLE State changed to "); /* EXPERIMENTAL */
      break;
    case RobotValue::RobotState:
      robot_state = (RobotState) data; 
      RPC.print("Robot State changed to "); /* EXPERIMENTAL */
      break;
    case RobotValue::DriveSpeed:
      cur_drive_speed = data;
      RPC.print("Drive Speed changed to "); /* EXPERIMENTAL */
      break;
    case RobotValue::DriveDirection:
      cur_drive_direction = data;
      RPC.print("Drive Direcion changed to "); /* EXPERIMENTAL */
      break;
    case RobotValue::ServoTurnHead:
      Servos::write(Servos::TURN_HEAD, max(min(data, 180), 0));
      RPC.print("Servo turn head to "); /* EXPERIMENTAL */
      break;
    case RobotValue::ServoTiltHead:
      Servos::write(Servos::TILT_HEAD, max(min(data, 180), 0));
      RPC.print("Servo tilt head to "); /* EXPERIMENTAL */
      break;
    case RobotValue::ServoArmLeft:
      Servos::write(Servos::ARM_LEFT, max(min(data, 180), 0));
      RPC.print("Servo arm left to "); /* EXPERIMENTAL */
      break;
    case RobotValue::ServoHandLeft:
      Servos::write(Servos::HAND_LEFT, max(min(data, 180), 0));
      RPC.print("Servo hand left to "); /* EXPERIMENTAL */
      break;
    case RobotValue::ServoArmRight:
      Servos::write(Servos::ARM_RIGHT, max(min(data, 180), 0));
      RPC.print("Servo arm right to "); /* EXPERIMENTAL */
      break;
    case RobotValue::ServoHandRight:
      Servos::write(Servos::HAND_RIGHT, max(min(data, 180), 0));
      RPC.print("Servo hand right to "); /* EXPERIMENTAL */
      break;
  }
  RPC.println(data); /* EXPERIMENTAL */
  setEyeStates(); /* EXPERIMENTAL */
}

void runBLEDisconnectButtonThread() {
  if (!digitalRead(BLE_PAIR_BUTTON_PIN)) {
    RPC.call("disconnectBLE");
  }
}

void runBLEStatusLEDThread() {
  if (ble_state == BLEState::Advertising) 
    digitalWrite(BLE_STATUS_LED_PIN, millis()%1000 < 500);
  else if (ble_state == BLEState::Connecting) 
    digitalWrite(BLE_STATUS_LED_PIN, millis()%250 < 125);
  else if (ble_state == BLEState::Connected) 
    digitalWrite(BLE_STATUS_LED_PIN, HIGH);
}

void runDrivingThread() {
  Motors::drive(cur_drive_speed, cur_drive_direction);
}

/* EXPERIMENTAL */
void setEyeStates() {
  if (robot_state == RobotState::Disconnected)
    Eyes::setState(Eyes::EyeState::RedSolid);
  else if (robot_state == RobotState::Authentication)
    Eyes::setState(Eyes::EyeState::GreenFast);
  else if (robot_state == RobotState::Running)
    Eyes::setState(Eyes::EyeState::GreenSolid);
  else if (robot_state == RobotState::Paused)
    Eyes::setState(Eyes::EyeState::GreenSlow);
  else if (robot_state == RobotState::Error)
    Eyes::setState(Eyes::EyeState::RedFast);
}
/* END_EXPERIMENTAL */
