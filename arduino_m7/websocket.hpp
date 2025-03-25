#ifndef ROBOT_WEBSOCKET_HPP
#define ROBOT_WEBSOCKET_HPP

#include <Arduino.h>
#include <WiFi.h>

class RobotWebSocket {

  public:

    RobotWebSocket();
    bool init();
    void updateConnection();
    void updateClient();
    
  private:

    void performHandshake(String key);
    String websocketHandshakeAccept(String websocket_key);

    WiFiServer wifi_server;
    WiFiClient socket_client;
    bool is_connected = false;

};

#endif