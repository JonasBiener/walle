#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <RPC.h>
#include <ArduinoBLE.h>

namespace BluetoothLE {

  BLEService authenticaton_service("98bb0c51-1d1b-4100-98b7-f2b494c1d6e3");
  BLEUnsignedIntCharacteristic authentication_array_characteristic("d37c30a4-16c4-4106-87b2-20eb0a234b3a", BLERead | BLEWrite);
  BLEDescriptor authentication_array_descriptor("b0ffce1a-dd7a-4053-8d5d-08a037ff20a2", "Authentication Array");
  void onAuthenticationArrayCharacteristicChange(BLEDevice, BLECharacteristic) { validateAuthenticationArray(authentication_array_characteristic.value()); }
  BLEShortCharacteristic authentication_confirm_characteristic("38ded87d-8807-4262-aba9-01f5d9a01a20", BLERead);
  BLEDescriptor authentication_confirm_descriptor("e2c078f2-320f-4733-accb-30ade02586a9", "Authentication Confirmed");
  void setAuthenticationArrayConfirmCharacteristic(int16_t value) { authentication_confirm_characteristic.writeValue(value); }
  
  void buildAuthenticationService() {
    authentication_array_characteristic.addDescriptor(authentication_array_descriptor);
    authentication_array_characteristic.setEventHandler(BLEWritten, onAuthenticationArrayCharacteristicChange);
    authentication_array_characteristic.setValue(0);
    drive_service.addCharacteristic(authentication_array_characteristic);
    authentication_confirm_characteristic.addDescriptor(authentication_confirm_descriptor);
    authentication_confirm_characteristic.setValue(0);
    drive_service.addCharacteristic(authentication_confirm_characteristic);
    BLE.addService(authenticaton_service);
  }
  
  BLEService drive_service("6d4d2d45-c51b-4034-bd72-4d134d8d8f9e");
  BLEShortCharacteristic drive_speed_characteristic("e92ab9ad-e970-44ca-b78a-0708fe306c3c", BLERead | BLEWrite);
  BLEDescriptor drive_speed_descriptor("cf57dcfb-4239-45ae-8715-4551d2852611", "Driving Speed");
  void onDriveSpeedCharacteristicChange(BLEDevice, BLECharacteristic) { synchronizeRobotValues(RobotValue::DriveSpeed, drive_speed_characteristic.value()); }
  BLEShortCharacteristic drive_direction_characteristic("ae21bd14-732c-46dc-a82b-fc0e23e2d36e", BLERead | BLEWrite);
  BLEDescriptor drive_direction_descriptor("ea567052-7bd9-44d0-a211-41e116f37383", "Driving Direction");
  void onDriveDirectionCharacteristicChange(BLEDevice, BLECharacteristic) { synchronizeRobotValues(RobotValue::DriveDirection, drive_direction_characteristic.value()); }

  void buildDriveService() {
    drive_speed_characteristic.addDescriptor(drive_speed_descriptor);
    drive_speed_characteristic.setEventHandler(BLEWritten, onDriveSpeedCharacteristicChange);
    drive_speed_characteristic.setValue(0);
    drive_service.addCharacteristic(drive_speed_characteristic);
    drive_direction_characteristic.addDescriptor(drive_direction_descriptor);
    drive_direction_characteristic.setEventHandler(BLEWritten, onDriveDirectionCharacteristicChange);
    drive_direction_characteristic.setValue(0);
    drive_service.addCharacteristic(drive_direction_characteristic);
    BLE.addService(drive_service);
  }

  BLEService servo_service("2dcc1369-d461-4dfe-b9e7-f91521d0315d");
  BLEShortCharacteristic servo_turn_head_characteristic("47479496-50d5-4072-ab21-f09bfd5a317c", BLERead | BLEWrite);
  BLEDescriptor servo_turn_head_descriptor("38c0622e-db0e-44d1-abed-aec424b66a70", "Turn Head Servo");
  void onServoTurnHeadChange(BLEDevice, BLECharacteristic) { synchronizeRobotValues(RobotValue::ServoTurnHead, servo_turn_head_characteristic.value()); }
  BLEShortCharacteristic servo_tilt_head_characteristic("23ef21b2-77b6-4325-9a38-f109000bb31a", BLERead | BLEWrite);
  BLEDescriptor servo_tilt_head_descriptor("44b6a4db-5cdf-4bef-b296-4374861a6a8c", "Tilt Head Servo");
  void onServoTiltHeadChange(BLEDevice, BLECharacteristic) { synchronizeRobotValues(RobotValue::ServoTiltHead, servo_tilt_head_characteristic.value()); }
  BLEShortCharacteristic servo_arm_left_characteristic("75c91dff-f7d0-4e90-ad5b-f1686cd44ada", BLERead | BLEWrite);
  BLEDescriptor servo_arm_left_descriptor("a4d980c2-707e-434d-94f8-74fc67cb24b5", "Arm Left Servo");
  void onServoArmLeftChange(BLEDevice, BLECharacteristic) { synchronizeRobotValues(RobotValue::ServoArmLeft, servo_arm_left_characteristic.value()); }
  BLEShortCharacteristic servo_hand_left_characteristic("97b6572b-4d4e-4d98-8c33-133a1dc012f9", BLERead | BLEWrite);
  BLEDescriptor servo_hand_left_descriptor("725c25ad-7569-44c2-b3e1-61bf09e72964", "Hand Left Servo");
  void onServoHandLeftChange(BLEDevice, BLECharacteristic) { synchronizeRobotValues(RobotValue::ServoHandLeft, servo_hand_left_characteristic.value()); }
  BLEShortCharacteristic servo_arm_right_characteristic("98f2ce86-1e87-49ee-8c57-729c1b1f0e82", BLERead | BLEWrite);
  BLEDescriptor servo_arm_right_descriptor("15b4b717-2225-4d82-b336-48630fb51109", "Arm Right Servo");
  void onServoArmRightChange(BLEDevice, BLECharacteristic) { synchronizeRobotValues(RobotValue::ServoArmRight, servo_arm_right_characteristic.value()); }
  BLEShortCharacteristic servo_hand_right_characteristic("22287c1d-6dab-49af-bcd8-f640aed701ee", BLERead | BLEWrite);
  BLEDescriptor servo_hand_right_descriptor("8072b002-5ea5-441e-ba0e-46248d86b6b0", "Hand Right Servo");
  void onServoHandRightChange(BLEDevice, BLECharacteristic) { synchronizeRobotValues(RobotValue::ServoHandRight, servo_hand_right_characteristic.value()); }

  void buildServoService() {
    servo_turn_head_characteristic.addDescriptor(servo_turn_head_descriptor);
    servo_turn_head_characteristic.setEventHandler(BLEWritten, onServoTurnHeadChange);
    servo_turn_head_characteristic.setValue(SERVO_TURN_HEAD_INITIAL);
    drive_service.addCharacteristic(servo_turn_head_characteristic);
    servo_tilt_head_characteristic.addDescriptor(servo_tilt_head_descriptor);
    servo_tilt_head_characteristic.setEventHandler(BLEWritten, onServoTiltHeadChange);
    servo_tilt_head_characteristic.setValue(SERVO_TILT_HEAD_INITIAL);
    drive_service.addCharacteristic(servo_tilt_head_characteristic);
    servo_arm_left_characteristic.addDescriptor(servo_arm_left_descriptor);
    servo_arm_left_characteristic.setEventHandler(BLEWritten, onServoArmLeftChange);
    servo_arm_left_characteristic.setValue(SERVO_ARM_LEFT_INITIAL);
    drive_service.addCharacteristic(servo_arm_left_characteristic);
    servo_hand_left_characteristic.addDescriptor(servo_hand_left_descriptor);
    servo_hand_left_characteristic.setEventHandler(BLEWritten, onServoHandLeftChange);
    servo_hand_left_characteristic.setValue(SERVO_HAND_LEFT_INITIAL);
    drive_service.addCharacteristic(servo_hand_left_characteristic);
    servo_arm_right_characteristic.addDescriptor(servo_arm_right_descriptor);
    servo_arm_right_characteristic.setEventHandler(BLEWritten, onServoArmRightChange);
    servo_arm_right_characteristic.setValue(SERVO_ARM_RIGHT_INITIAL);
    drive_service.addCharacteristic(servo_arm_right_characteristic);
    servo_hand_right_characteristic.addDescriptor(servo_hand_right_descriptor);
    servo_hand_right_characteristic.setEventHandler(BLEWritten, onServoHandRightChange);
    servo_hand_right_characteristic.setValue(SERVO_HAND_RIGHT_INITIAL);
    drive_service.addCharacteristic(servo_hand_right_characteristic);
    BLE.addService(servo_service);
  }

  BLEService eye_service("770e772d-3633-49fb-8345-997d2a0d3933");
  BLEShortCharacteristic eye_color_characteristic("79888994-2b3f-400d-b6bf-370bac7afb6f", BLERead | BLEWrite);
  BLEDescriptor eye_color_descriptor("76fd5471-cedf-4c27-a8dd-b5e86d926583", "Eye Color");
  void onEyeColorChange(BLEDevice, BLECharacteristic);
  BLEShortCharacteristic eye_style_characteristic("3e8ebb25-6370-493e-8d22-2bb12f45ad57", BLERead | BLEWrite);
  BLEDescriptor eye_style_descriptor("c8fc6255-0ae1-4b08-85c6-116a280c7c1e", "Eye Style");
  void onEyeStyleChange(BLEDevice, BLECharacteristic);

  void buildEyeService() {
    eye_color_characteristic.addDescriptor(eye_color_descriptor);
    eye_color_characteristic.setEventHandler(BLEWritten, onEyeColorChange);
    eye_color_characteristic.setValue(0);
    eye_service.addCharacteristic(eye_color_characteristic);
    eye_style_characteristic.addDescriptor(eye_style_descriptor);
    eye_style_characteristic.setEventHandler(BLEWritten, onEyeStyleChange);
    eye_style_characteristic.setValue(0);
    eye_service.addCharacteristic(eye_style_characteristic);
    BLE.addService(eye_service);
  }

  void onConnect(BLEDevice);
  void onDisconnect(BLEDevice);

  void init() {
    if (!BLE.begin()) {
      Serial.println("ERR: Starting Bluetooth® Low Energy failed.");
      return;
    }
    BLE.setLocalName("WALL-E");
    BLE.setDeviceName("RoCCI e.V.");
    BLE.setAdvertisedService(drive_service);
    BLE.setEventHandler(BLEConnected, onConnect);
    BLE.setEventHandler(BLEDisconnected, onDisconnect);
    buildDriveService();
    buildServoService();
    buildEyeService();
    BLE.advertise();
    RPC.println("Bluetooth® Low Energy initialized.");
  }

  void disconnect() {
    BLE.disconnect();
  }

}
