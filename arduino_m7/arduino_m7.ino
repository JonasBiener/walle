#include "F:/GitHub/walle/arduino_common/definitions.hpp" // Change according to source-path

#include <RPC.h>
#include <ArduinoBLE.h>

void synchronizeRobotValues(RobotValue robot_value, int16_t data);
void changeBLEState(BLEState state);
void changeRobotState(RobotState state);

#include "authentication.hpp" // Handles user-authentication
#include "bluetoothLE.hpp" // Defines BLE service-structure and characteristics

BLEState ble_state = BLEState::Initial;
RobotState robot_state = RobotState::Disconnected;

void BluetoothLE::onConnect(BLEDevice central) {
  Serial.print("Bluetooth® Low Energy connected to central: ");
  Serial.println(central.address());
  changeBLEState(BLEState::Connected);
  changeRobotState(RobotState::Running);
  // Authentication::initiateAuthentication();
}

void BluetoothLE::onDisconnect(BLEDevice central) {
  Serial.print("Bluetooth® Low Energy disconnected from central: ");
  Serial.println(central.address());
  changeBLEState(BLEState::Advertising);
  changeRobotState(RobotState::Disconnected);
}

void setup() {
  RPC.begin();
  RPC.bind("disconnectBLE", BluetoothLE::disconnect);
  Serial.begin(115200);
  BluetoothLE::init();
  Serial.println("Bluetooth® Low Energy active, waiting for connections...");
}

void loop() {
  BLE.poll();
  if (RPC.available()) {
    Serial.print((char) RPC.read());
  }
}

void synchronizeRobotValues(RobotValue robot_value, int16_t data) {
  RPC.call("setRobotValue", (uint8_t) robot_value, data);
}

void changeBLEState(BLEState state) {
  ble_state = state;
  synchronizeRobotValues(RobotValue::BLEState, (int16_t) state);
}

void changeRobotState(RobotState state) {
  robot_state = state;
  synchronizeRobotValues(RobotValue::RobotState, (int16_t) state);
}
