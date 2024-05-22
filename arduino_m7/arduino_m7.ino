#include <RPC.h>
#include <ArduinoBLE.h>

BLEService ledService("E5242354-9449-4C07-83AA-55780467604C");
BLEByteCharacteristic stateCharacteristic("1EB8412D-A87D-45C9-941D-5C3F48C35F4C", BLERead | BLEWrite);
BLEDescriptor stateCharacteristicDescriptor("098D40A4-F1DB-4719-B418-3D5F714992C8", "LED State");

// #define BUTTON_PAIR_PIN 5

uint8_t led_state = 0;

void setup() {
  RPC.begin();
  Serial.begin(9600);
  // pinMode(BUTTON_PAIR_PIN, INPUT_PULLUP);
  RPC.call("setBTState", 2);
  Serial.println("Starting Bluetooth® Low Energy device...");
  if (!BLE.begin()) {
    Serial.println("Starting Bluetooth® Low Energy device failed!");
    while (1);
  }
  BLE.setLocalName("LEDController");
  BLE.setAdvertisedService(ledService);
  BLE.setEventHandler(BLEConnected, btConnectHandler);
  BLE.setEventHandler(BLEDisconnected, btDisconnectHandler);
  stateCharacteristic.setEventHandler(BLEWritten, ledStateWrittenHandler);
  stateCharacteristic.addDescriptor(stateCharacteristicDescriptor);
  stateCharacteristic.setValue(0);
  ledService.addCharacteristic(stateCharacteristic);
  BLE.addService(ledService);
  BLE.advertise();
  RPC.call("setBTState", 1);
  Serial.println(("Bluetooth® device active, waiting for connections..."));
}

void loop() {
  BLE.poll();
}

void btConnectHandler(BLEDevice central) {
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
  RPC.call("setBTState", 3);
}

void btDisconnectHandler(BLEDevice central) {
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
  RPC.call("setBTState", 1);
}

void ledStateWrittenHandler(BLEDevice central, BLECharacteristic characteristic) {
  uint8_t value = stateCharacteristic.value();
  Serial.print("Characteristic event, written: ");
  Serial.println(value);
  RPC.call("setLEDState", value);
}
