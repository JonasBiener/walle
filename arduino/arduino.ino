// #include "filesystem.hpp"
// #include "webserver.hpp"
// #include "websocket.hpp"

#include "servos.hpp"
#include "driving.hpp"

// RobotFilesystem file_system{};
// RobotWebServer web_server{file_system};
// RobotWebSocket web_socket{};

RobotServos servos{};
RobotDriving driving {};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Booted up M7");

  // if (!file_system.init()) {
  //   while (true);
  // }

  // if (!web_server.init()) {
  //   while (true);
  // }

  // web_socket.init();
  // web_server.logServerStatus();

  driving.init();
  // servos.init();
  
}

void loop() {
  // web_server.updateConnection();
  // web_server.updateClient();  
  // web_socket.updateConnection();
  // web_socket.updateClient();

  driving.drive(0, 100);
  driving.drive(0, -100);
  driving.drive(255, 100);
  driving.drive(-255, 100);
  driving.drive(255, -100);
  driving.drive(-255, -100);
}
