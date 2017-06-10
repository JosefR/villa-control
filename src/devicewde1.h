#ifndef DEVICEWDE1_H
#define DEVICEWDE1_H

#include <string>

#include "device.h"
#include "serialport.h"

namespace villa {

class DeviceWde1 : public Device {
public:
    DeviceWde1(std::map<std::string, std::string>& config);

    virtual ~DeviceWde1();

    virtual void init();

    virtual void deinit();

    virtual void start();

    virtual void stop();

    virtual void processReadData(std::vector<uint8_t>& buf, int& size);

    virtual void getSendData(std::vector<uint8_t>& buf, int& size);

private:
    void handleEventRead();

private:
};

}  // namespace villa

#endif  // DEVICEWDE1_H
