#include "WiFiClient.h"
#include "websocket.hpp"

#include <mbedtls/sha1.h>
#include <mbedtls/base64.h>

RobotWebSocket::RobotWebSocket() :
  wifi_server{8080},
  socket_client{} {}

bool RobotWebSocket::init() {
  wifi_server.begin();
  Serial.print("WebSocket initialized");
  return true;
}

void RobotWebSocket::updateConnection() {
  if (!socket_client.connected()) {
    WiFiClient client = wifi_server.accept();
    if (client) {
      socket_client = client;
      Serial.println("new websocket client connected"); // DEBUG
    }
  }
}

void RobotWebSocket::updateClient() {
  if (socket_client && socket_client.connected()) {
    String currentLine = "";
    String currentValue = "";
    while (socket_client.available()) {
      digitalWrite(10, HIGH); // DEBUG
      if (!is_connected) {
        char c = socket_client.read();
        Serial.write(c); // DEBUG
        if (c == '\n') {
          if (currentLine.length() == 0) {
            if (currentValue.length() > 0) performHandshake(currentValue);
            is_connected = true;
            break;
          }
          else if (currentLine.startsWith("Sec-WebSocket-Key")) {
            currentValue = currentLine.substring(19);
            currentValue.trim();
          }
          currentLine = "";
        }
        else if (c != '\r') {
          currentLine += c;
        }
      }
      else {
        char c = socket_client.read();
        Serial.print(c, HEX); // DEBUG
      }
    }
    digitalWrite(10, LOW); // DEBUG
  }
}

void RobotWebSocket::performHandshake(String key) {
  socket_client.println("HTTP/1.1 101 Switching Protocols");
  socket_client.println("Upgrade: websocket");
  socket_client.println("Connection: Upgrade");
  String websocket_accept = websocketHandshakeAccept(key);
  socket_client.println(String("Sec-WebSocket-Accept: ") + websocket_accept);
  socket_client.println();
}

String RobotWebSocket::websocketHandshakeAccept(String websocket_key) {
  String hash_input = websocket_key + String("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
  unsigned char sha1hash[20];
  mbedtls_sha1_ret(reinterpret_cast<const unsigned char*>(hash_input.c_str()), (size_t) hash_input.length(), sha1hash);
  unsigned char base64result[32];
  size_t written_bytes;
  mbedtls_base64_encode(base64result, 32, &written_bytes, sha1hash, 20);
  return String(reinterpret_cast<const char*>(base64result), written_bytes);
}