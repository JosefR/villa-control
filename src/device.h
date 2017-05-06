#ifndef DEVICE_H
#define DEVICE_H

#include <map>
#include <list>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <iostream>

#include "sensor.h"
#include "actuator.h"

namespace villa {

class Device {
   public:
    Device(std::map<std::string, std::string>& config);
    virtual ~Device();

    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

    std::string name() const;

    virtual void processReadData(std::vector<uint8_t>& buf, int& size) = 0;
    virtual void getSendData(std::vector<uint8_t>& buf, int& size) = 0;

   private:
   protected:
    std::string mName;

    std::list<std::shared_ptr<Sensor>> mSensors;
    std::list<std::shared_ptr<Actuator>> mActuators;

    std::map<std::string, std::string> mConfig;

    int mFd;
};

}  // namespace villa

#endif  // DEVICE_H
