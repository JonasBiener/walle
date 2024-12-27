#ifdef CORE_CM7

#include "filesystem.hpp"
#include "webserver.hpp"

RobotFilesystem file_system{};
RobotWebServer web_server{file_system};

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Booted up M7");

  pinMode(10, OUTPUT); 
  digitalWrite(10, LOW);

  if (!file_system.init()) {
    while (true);
  }

  if (!web_server.init()) {
    while (true);
  }

  web_server.logServerStatus();
}

void loop() {
  web_server.updateConnection();
  web_server.updateClient();
}

#endif

#ifdef CORE_CM4

#error Code for Cortex M4 is not yet implemented

#endif