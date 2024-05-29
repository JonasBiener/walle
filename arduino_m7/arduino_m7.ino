#include "F:/GitHub/walle/arduino_common/definitions.hpp" // Change according to source-path

#include <RPC.h>
#include <ArduinoBLE.h>

void synchronizeRobotValues(RobotValue robot_value, int16_t data) {
  RPC.call("setRobotValue", (uint8_t) robot_value, data);
}

#include "bluetoothLE.hpp" // Defines BLE service-structure and characteristics

BLEState ble_state = BLEState::Advertising;
RobotState robot_state = RobotState::Disconnected;

void BluetoothLE::onConnect(BLEDevice central) {
  Serial.print("Bluetooth® Low Energy connected to central: ");
  Serial.println(central.address());
  ble_state = BLEState::Connected;
  robot_state = RobotState::Running;
  synchronizeRobotValues(RobotValue::BLEState, (int16_t) ble_state);
  synchronizeRobotValues(RobotValue::RobotState, (int16_t) robot_state);
}

void BluetoothLE::onDisconnect(BLEDevice central) {
  Serial.print("Bluetooth® Low Energy disconnected from central: ");
  Serial.println(central.address());
  ble_state = BLEState::Advertising;
  robot_state = RobotState::Disconnected;
  synchronizeRobotValues(RobotValue::BLEState, (int16_t) ble_state);
  synchronizeRobotValues(RobotValue::RobotState, (int16_t) robot_state);
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
