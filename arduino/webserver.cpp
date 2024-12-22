#include "pure_analog_pins.h"
#include "webserver.hpp"

RobotWebServer::RobotWebServer() : 
  wifi_server{80}, 
  server_ip_address{IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]},
  wifi_udp{},
  mdns{wifi_udp} {}

bool RobotWebServer::init() {
  Serial.println("Initializing web server");
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("ERROR: WiFi-Module not accessible");
    return false;
  }
  WiFi.config(server_ip_address);
  if (access_point) {
    Serial.print("Creating access point named: ");
    Serial.println(SSID);
    status = WiFi.beginAP(SSID, PASSWORD);
    if (status != WL_AP_LISTENING) {
      Serial.println("ERROR: Failed creating access point");
      return false;
    }
  }
  else {
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to network named: ");
      Serial.println(SSID);
      status = WiFi.begin(SSID, PASSWORD);
      delay(3000);
    }
  }
  
  wifi_server.begin();
  Serial.print("Registering mdns hostname:");
  Serial.println(HOSTNAME);
  if (!mdns.begin(WiFi.localIP(), HOSTNAME)) { 
    Serial.println("ERROR: Failed starting mdns service");
    return false;
  }
  mdns.addServiceRecord("RobotWebServer._http" , 80, MDNSServiceTCP);
  Serial.println("Web server initialized");
  return true;
}

void RobotWebServer::logServerStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP-Address: ");
  Serial.println(ip);
  Serial.print("Server is accessible at http://");
  Serial.print(ip);
  Serial.print(" and http://");
  Serial.print(HOSTNAME);
  Serial.println(".local");
}

void RobotWebServer::updateConnection() {
  mdns.run();
  if (status != WiFi.status()) {
    status = WiFi.status();
    if (access_point && status == WL_AP_CONNECTED) {
      Serial.println("Device connected to access point");
      digitalWrite(10, HIGH);
    } 
    else if (access_point) {
      Serial.println("Device disconnected from access point");
      digitalWrite(10, LOW);
    }
    else if (!access_point && status == WL_CONNECTED) {
      Serial.println("Robot connected to wifi");
      digitalWrite(10, HIGH);
    }
    else {
      Serial.println("Robot disconnected from wifi");
      digitalWrite(10, LOW);
    }
  }
}

void RobotWebServer::updateClient() {
  WiFiClient client = wifi_server.accept();
  if (client) {
    Serial.println("new client"); // DEBUG
    String currentLine = "";
    String ressource = "";
    String request_type = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c); // DEBUG
        if (c == '\n') {
          if (currentLine.length() == 0) {
            if (request_type == "GET") respondGetRequest(client, ressource);
            else if (request_type == "POST") respondPostRequest(client, ressource);
            break;
          }
          else {
            if (currentLine.startsWith("GET")) {
              ressource = currentLine.substring(4);
              ressource = ressource.substring(0, ressource.indexOf(' '));
              request_type = "GET";
            }
            else if (currentLine.startsWith("POST")) {
              ressource = currentLine.substring(5);
              ressource = ressource.substring(0, ressource.indexOf(' '));
              request_type = "POST";
            }
            currentLine = "";
          }
        }
        else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("client disconnected"); // DEBUG
  }
}

void RobotWebServer::respondHTTPRequest(WiFiClient &client, int status_code, String status_description, String header_concat) {
  String response = String("HTTP/1.1 ") + String(status_code) + String(" ") + status_description + String("\n") + header_concat;
  client.print(response);
}

void RobotWebServer::respondHTTPRequestStatus(WiFiClient &client, int status_code, String status_description) {
  respondHTTPRequest(client, status_code, status_description, "\n");
}

void RobotWebServer::respondHTTPRequestContent(WiFiClient &client, int status_code, String status_description, String content_type, String content) {
  String concat = String("Content-Type: ") + content_type + String("\n") + String("\n") + content;
  respondHTTPRequest(client, status_code, status_description, concat);
}

void RobotWebServer::respondGetRequest(WiFiClient &client, String ressource) {
  respondHTTPRequestContent(client, 200, "OK", "text/plain", "The GET ressource is " + ressource);
}

void RobotWebServer::respondPostRequest(WiFiClient &client, String ressource) {
  respondHTTPRequestContent(client, 200, "OK", "text/plain", "The POST ressource is " + ressource);
}