// Code for ARM Cortex M7 Core
#ifdef CORE_CM7

#include <RPC.h>

#include "filesystem.hpp"
#include "webserver.hpp"
#include "websocket.hpp"

RobotFilesystem file_system{};
RobotWebServer web_server{file_system};
RobotWebSocket web_socket{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Booted up M7");
  RPC.begin();

  pinMode(8, OUTPUT); // DEBUG
  pinMode(9, OUTPUT); // DEBUG
  pinMode(10, OUTPUT); // DEBUG

  if (!file_system.init()) {
    while (true);
  }

  if (!web_server.init()) {
    while (true);
  }

  web_socket.init();
  web_server.logServerStatus();
}

void loop() {
  digitalWrite(8, HIGH); // DEBUG
  String buffer = "";
  while (RPC.available()) buffer += (char) RPC.read();
  if (buffer.length() > 0) Serial.print(buffer);
  web_server.updateConnection();
  web_server.updateClient();  
  web_socket.updateConnection();
  web_socket.updateClient();
  delay(10); // DEBUG
  digitalWrite(8, LOW); // DEBUG
  delay(20); // DEBUG
}

#endif


// Code for ARM Cortex M4 Core
#ifdef CORE_CM4

#include <RPC.h>

#include "servos.hpp"

void setup() {
  RPC.println("M4: Booted up M4");
  Servos.init();
}

void loop() {
  Servos.write(Servos.turn_head, 0);
  delay(1000);
  Servos.write(Servos.tilt_head, 0);
  delay(1000);
  Servos.write(Servos.arm_left, 0);
  delay(1000);
  Servos.write(Servos.hand_left, 0);
  delay(1000);
  Servos.write(Servos.arm_right, 0);
  delay(1000);
  Servos.write(Servos.hand_right, 0);
  delay(1000);
  Servos.write(Servos.turn_head, 180);
  delay(1000);
  Servos.write(Servos.tilt_head, 180);
  delay(1000);
  Servos.write(Servos.arm_left, 180);
  delay(1000);
  Servos.write(Servos.hand_left, 180);
  delay(1000);
  Servos.write(Servos.arm_right, 180);
  delay(1000);
  Servos.write(Servos.hand_right, 180);
  delay(1000);
}

#endif