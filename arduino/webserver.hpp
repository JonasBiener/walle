#ifndef ROBOT_WEBSERVER_HPP
#define ROBOT_WEBSERVER_HPP

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoMDNS.h>

// #include "secrets.hpp"
#include "filesystem.hpp"

class RobotWebServer {

  public:

    RobotWebServer(RobotFilesystem& file_system_);
    bool init();
    void logServerStatus();
    void updateConnection();
    void updateClient();

  private:

    const bool access_point = true;
    const char SSID[16] = "WALL-E Robot"; // "WALL-E Robot"; WIFI_SSID;
    const char PASSWORD[16] = "rocciwalle"; // "rocciwalle"; WIFI_PASSWORD;
    const unsigned char IP_ADDRESS[4] = {192, 168, 178, 10}; // {10, 10, 10, 10};
    const char HOSTNAME[8] = "robot";
    const size_t buffer_size = 10000;
    const int connection_timeout = 2000;

    int status = WL_IDLE_STATUS;
    RobotFilesystem& file_system;
    WiFiServer wifi_server;
    IPAddress server_ip_address;
    WiFiUDP wifi_udp;
    MDNS mdns;
      
    void respondGetRequest(WiFiClient& client, String ressource);
    void respondRedirect(WiFiClient& client, String target);
    void respondStartLine(WiFiClient& client, int status_code, String status_description);
    void respondAddHeader(WiFiClient& client, String header, String value);
    void respondEndHeaders(WiFiClient& client);
    void respondDirect(WiFiClient& client, String response);
    void respondDirect(WiFiClient& client, char* buff, size_t buff_size);

};

#endif