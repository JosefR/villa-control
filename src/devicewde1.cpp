#include <sys/types.h>
#include <sys/stat.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "devicewde1.h"

namespace villa {

DeviceWde1::DeviceWde1(std::map<std::string, std::string> &config)
    : Device(config)
{
    std::cerr << "DeviceWde1::DeviceWde1" << std::endl;

}

DeviceWde1::~DeviceWde1()
{
    std::cerr << "DeviceWde1::~DeviceWde1" << std::endl;
}

void DeviceWde1::init()
{
}

void DeviceWde1::deinit()
{
}

void DeviceWde1::start()
{

}

void DeviceWde1::stop()
{

}

void DeviceWde1::processReadData(std::vector<uint8_t> &buf, int &size)
{

}

void DeviceWde1::getSendData(std::vector<uint8_t> &buf, int &size)
{

}

} // namespace villa
