#include "webserver.hpp"
#include "filesystem.hpp"

// RobotWebServer web_server;
RobotFilesystem file_system;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Booted up M7");

  // pinMode(LED_BUILTIN, OUTPUT); 
  // pinMode(10, OUTPUT);
  // digitalWrite(10, LOW);

  // if (!web_server.init()) {
  //   while (true);
  // }
  // web_server.logServerStatus();
  if (!file_system.init()) {
    while (true);
  }
  String file = file_system.readFile("/myfolder/example.txt");
  Serial.println(file);
}

void loop() {
  // web_server.updateConnection();
  // web_server.updateClient();
}