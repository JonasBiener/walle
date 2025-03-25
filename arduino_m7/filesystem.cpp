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

std::unique_ptr<mbed::File> RobotFilesystem::openFile(String filename) {
  std::unique_ptr<mbed::File> file_ptr{new mbed::File};
  int errcode = file_ptr->open(&ota, filename.c_str(), O_RDONLY);
  if (errcode) {
    Serial.println(String("WARNING: File ") + filename + String(" could not be opened. [ ") + String(strerror(-errcode)) + String(" ]"));
    return std::unique_ptr<mbed::File>{};
  }
  return file_ptr;
}