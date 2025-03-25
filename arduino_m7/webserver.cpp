#include "webserver.hpp"

RobotWebServer::RobotWebServer(RobotFilesystem& file_system_) : 
  file_system{file_system_},
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
      delay(connection_timeout);
    }
  }
  
  wifi_server.begin();
  Serial.print("Registering mdns hostname: ");
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
    digitalWrite(9, HIGH); // DEBUG
    Serial.println("new client connected"); // DEBUG
    String currentLine = "";
    String ressource = "";
    String request_type = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // Serial.write(c); // DEBUG
        if (c == '\n') {
          if (currentLine.length() == 0) {
            if (request_type == "GET") respondGetRequest(client, ressource);
            else if (request_type == "POST") respondStartLine(client, 405, "Method Not Allowed");
            else respondStartLine(client, 400, "Bad Request");
            break;
          }
          else {
            if (currentLine.startsWith("GET")) {
              Serial.println(currentLine); // DEBUG
              ressource = currentLine.substring(4);
              ressource = ressource.substring(0, ressource.indexOf(' '));
              ressource.trim();
              request_type = "GET";
            }
            else if (currentLine.startsWith("POST")) {
              Serial.println(currentLine); // DEBUG
              ressource = currentLine.substring(5);
              ressource = ressource.substring(0, ressource.indexOf(' '));
              ressource.trim();
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
  digitalWrite(9, LOW); // DEBUG
}

void RobotWebServer::respondGetRequest(WiFiClient& client, String ressource) {
  // Redirect empty path to index.html
  if (ressource == "/") return respondRedirect(client, "/index.html");
  if (ressource == "/favicon.ico") return respondRedirect(client, "/walleBox.ico");
  // Remove query string
  if (ressource.indexOf('?') > 0) ressource = ressource.substring(0, ressource.indexOf('?'));
  // Search for file on internal memory
  auto file = file_system.openFile(ressource);
  if (!file) return respondStartLine(client, 404, "Not Found");
  // Start http response
  respondStartLine(client, 200, "OK");
  // Add content type
  if (ressource.endsWith(".html")) respondAddHeader(client, "Content-Type: ", "text/html");
  else if (ressource.endsWith(".svg")) respondAddHeader(client, "Content-Type: ", "image/svg+xml");
  else if (ressource.endsWith(".js")) respondAddHeader(client, "Content-Type: ", "text/javascript");
  else if (ressource.endsWith(".css")) respondAddHeader(client, "Content-Type: ", "text/css");
  else respondAddHeader(client, "Content-Type: ", "text/plain");
  // Add content length
  respondAddHeader(client, "Content-Length: ", String(file->size()));
  // Add connection header
  respondAddHeader(client, "Connection: ", "keep-alive");
  // End headers
  respondEndHeaders(client);
  // Stream file
  unsigned int read_size = 0;
  char buffer[buffer_size];
  do {
    read_size = file->read(buffer, buffer_size);
    respondDirect(client, buffer, read_size);
  } while (read_size == buffer_size);
}

void RobotWebServer::respondRedirect(WiFiClient& client, String target) {
  respondStartLine(client, 302, "Found");
  respondDirect(client, String("Location: ") + target);
  respondEndHeaders(client);
}

void RobotWebServer::respondStartLine(WiFiClient& client, int status_code, String status_description) {
  client.println(String("HTTP/1.1 ") + String(status_code) + String(" ") + status_description);
}

void RobotWebServer::respondAddHeader(WiFiClient& client, String header, String value) {
  client.println(header + value);
}

void RobotWebServer::respondEndHeaders(WiFiClient& client) {
  client.println();
}

void RobotWebServer::respondDirect(WiFiClient& client, String response) {
  client.print(response);
}

void RobotWebServer::respondDirect(WiFiClient& client, char* buff, size_t buff_size) {
  client.write(buff, buff_size);
}
