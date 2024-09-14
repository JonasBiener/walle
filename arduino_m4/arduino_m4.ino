#include "F:/GitHub/walle/arduino_common/definitions.hpp" // Change according to source-path

#include <RPC.h>

#include "servos.hpp" 
#include "motors.hpp" 
#include "eyes.hpp" 

BLEState ble_state = BLEState::Initial;
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
    case RobotValue::BLEState: {
      ble_state = (BLEState) data;  
      RPC.print("BLE State changed to "); /* EXPERIMENTAL */
      break;
    } 
    case RobotValue::RobotState: {
      robot_state = (RobotState) data; 
      changeRobotState();
      RPC.print("Robot State changed to "); /* EXPERIMENTAL */
      break;
    } 
    case RobotValue::DriveSpeed: {
      cur_drive_speed = (int16_t) ((float) data / 100.0 * 255.0);
      RPC.print("Drive Speed changed to "); /* EXPERIMENTAL */
      break;
    }
    case RobotValue::DriveDirection: {
      cur_drive_direction = (int16_t) ((float) data / 100.0 * 255.0);
      RPC.print("Drive Direcion changed to "); /* EXPERIMENTAL */
      break;
    }
    case RobotValue::ServoTurnHead: {
      int16_t converted = (int16_t) ((float) data / 100.0 * 180.0);
      Servos::write(Servos::TURN_HEAD, max(min(converted, 180), 0));
      RPC.print("Servo turn head to "); /* EXPERIMENTAL */
      break;
    }
    case RobotValue::ServoTiltHead: {
      int16_t converted = (int16_t) ((float) data / 100.0 * 180.0);
      Servos::write(Servos::TILT_HEAD, max(min(converted, 180), 0));
      RPC.print("Servo tilt head to "); /* EXPERIMENTAL */
      break;
    }
    case RobotValue::ServoArmLeft: {
      int16_t converted = (int16_t) ((float) data / 100.0 * 180.0);
      Servos::write(Servos::ARM_LEFT, max(min(converted, 180), 0));
      RPC.print("Servo arm left to "); /* EXPERIMENTAL */
      break;
    }
    case RobotValue::ServoHandLeft: {
      int16_t converted = (int16_t) ((float) data / 100.0 * 180.0);
      Servos::write(Servos::HAND_LEFT, max(min(converted, 180), 0));
      RPC.print("Servo hand left to "); /* EXPERIMENTAL */
      break;
    }
    case RobotValue::ServoArmRight: {
      int16_t converted = (int16_t) ((float) data / 100.0 * 180.0);
      Servos::write(Servos::ARM_RIGHT, max(min(converted, 180), 0));
      RPC.print("Servo arm right to "); /* EXPERIMENTAL */
      break;
    }
    case RobotValue::ServoHandRight: {
      int16_t converted = (int16_t) ((float) data / 100.0 * 180.0);
      Servos::write(Servos::HAND_RIGHT, max(min(converted, 180), 0));
      RPC.print("Servo hand right to "); /* EXPERIMENTAL */
      break;
    }
  }
  RPC.println(data); /* EXPERIMENTAL */
}

void runBLEDisconnectButtonThread() {
  if (!digitalRead(BLE_PAIR_BUTTON_PIN)) {
    RPC.call("disconnectBLE");
  }
}

void runBLEStatusLEDThread() {
  if (ble_state == BLEState::Initial) 
    digitalWrite(BLE_STATUS_LED_PIN, millis()%250 < 125);
  else if (ble_state == BLEState::Advertising) 
    digitalWrite(BLE_STATUS_LED_PIN, millis()%1000 < 500);
  else if (ble_state == BLEState::Connected) 
    digitalWrite(BLE_STATUS_LED_PIN, HIGH);
}

void runDrivingThread() {
  if (robot_state != RobotState::Running) {
    cur_drive_speed = 0;
    cur_drive_direction = 0;
  }
  Motors::drive(cur_drive_speed, cur_drive_direction);
}

void changeRobotState() {
  switch (robot_state) {
    case RobotState::Disconnected: {
      Eyes::setState(Eyes::EyeState::RedSolid);
    }  break;
    case RobotState::Authentication: {
      Eyes::setState(Eyes::EyeState::GreenFast);
    }  break;
    case RobotState::Running: {
      Eyes::setState(Eyes::EyeState::GreenSolid);
    }  break;
    case RobotState::Paused: {
      Eyes::setState(Eyes::EyeState::GreenSlow);
    }  break;
    case RobotState::Error: {
      Eyes::setState(Eyes::EyeState::RedFast);
    }  break;
  }
}