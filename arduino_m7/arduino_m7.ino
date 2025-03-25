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
  while (RPC.available()) Serial.print(RPC.read());
  web_server.updateConnection();
  web_server.updateClient();  
  web_socket.updateConnection();
  web_socket.updateClient();
  delay(10); // DEBUG
  digitalWrite(8, LOW); // DEBUG
  delay(20); // DEBUG
}
