#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoMDNS.h>

#include "secrets.hpp"

class RobotWebServer {
  public:

  RobotWebServer();
  bool init();
  void logServerStatus();
  void updateConnection();
  void updateClient();
  void respondHTTPRequest(WiFiClient &client, int status_code, String status_description, String header_concat);
  void respondHTTPRequestStatus(WiFiClient &client, int status_code, String status_description);
  void respondHTTPRequestContent(WiFiClient &client, int status_code, String status_description, String content_type, String content);
  void respondGetRequest(WiFiClient &client, String ressource);
  void respondPostRequest(WiFiClient &client, String ressource);

  private:

  const bool access_point = false;
  const char SSID[16] = WIFI_SSID; // "WALL-E Robot";
  const char PASSWORD[16] = WIFI_PASSWORD; // "rocciwalle";
  const int IP_ADDRESS[4] = {192, 168, 178, 10}; // {10, 10, 10, 10}
  const char HOSTNAME[8] = "robot";

  WiFiServer wifi_server;
  IPAddress server_ip_address;
  int status = WL_IDLE_STATUS;
  WiFiUDP wifi_udp;
  MDNS mdns;
};