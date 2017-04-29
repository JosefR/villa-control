#include "device.h"

namespace villa {

Device::Device(std::map<std::string, std::string> &config)
    : mName(config["name"]), mConfig(config), mFd(-1)
{
    std::cerr << "Device::Device" << std::endl;
}

Device::~Device()
{
    std::cerr << "Device::~Device" << std::endl;
}

std::string Device::name() const
{
    return mName;
}

} // namespace villa
