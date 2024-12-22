#include "filesystem.hpp"

RobotFilesystem::RobotFilesystem() :
  raw_qspi{mbed::BlockDevice::get_default_instance()}, 
  ota{"ota"}, 
  ota_data{raw_qspi, 2} {}

bool RobotFilesystem::init() {
  Serial.println("Initializing flash storage");
  if (ota.mount(&ota_data)) {
    Serial.println("ERROR: Could not mount flash storage");
    return false;
  }
  Serial.println("Flash storage initialized");
  return true;
}

String RobotFilesystem::readFile(String filename) {
  String path = String("/ota") + filename;
  FILE* f = fopen(path.c_str(), "r");
  if (errno) {
    Serial.println(String("WARNING: File ") + path + String(" could not be opened"));
    return "";
  }
  String file_content = "";
  const int buffer_size = 512;
  char buffer[buffer_size];
  int size = 0;
  do {
    size = fread(buffer, 1, buffer_size, f);
    // Serial.write(buffer, size);
    file_content += String(buffer);
  } while(size == buffer_size);
  fclose(f);
  return file_content;
}