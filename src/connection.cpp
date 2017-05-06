#include "connection.h"

namespace villa {

Connection::Connection()
{
}

void Connection::addDevice(std::shared_ptr<Device> dev)
{
    std::cout << "added Device: " << dev->name() << std::endl;
    mDevices.push_back(std::move(dev));
}

}  // namespace villa
