#ifndef VILLA_CONNECTION_H
#define VILLA_CONNECTION_H

#include <list>
#include <cstdint>

#include "device.h"

namespace villa {

class Connection {
   public:
    enum class IOState { FINISHED, AGAIN, ERROR };

   public:
    Connection();

    virtual void timeout() = 0;
    virtual void read() = 0;
    virtual void write() = 0;

    virtual int getFd() const = 0;

    void addDevice(std::shared_ptr<Device> dev);

   protected:
    std::list<std::shared_ptr<Device>> mDevices;
};

}  // namespace villa

#endif  // VILLA_CONNECTION_H
