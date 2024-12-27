#ifndef ROBOT_FILESYSTEM_H
#define ROBOT_FILESYSTEM_H

#include <Arduino.h>
#include <QSPIFBlockDevice.h>
#include <MBRBlockDevice.h>
#include <FATFileSystem.h>
#include <File.h>
#include <memory>

class RobotFilesystem {

  public:

    RobotFilesystem();
    bool init();
    std::unique_ptr<mbed::File> openFile(String filename);

  private:

    mbed::BlockDevice* raw_qspi;
    mbed::FATFileSystem ota;
    mbed::MBRBlockDevice ota_data;

};

#endif