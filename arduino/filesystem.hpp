#pragma once

#include <Arduino.h>
#include <QSPIFBlockDevice.h>
#include <MBRBlockDevice.h>
#include <FATFileSystem.h>

class RobotFilesystem {
  public:

  RobotFilesystem();
  bool init();
  String readFile(String filename);

  private:

  bool fileExists(String filename);
  mbed::BlockDevice* raw_qspi;
  mbed::FATFileSystem ota;
  mbed::MBRBlockDevice ota_data;
};