#include <string>
#include <algorithm>

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
    std::cerr << "DeviceWde1::processReadData" << std::endl;

    size_t k = 0;
    std::list<float> values;

    // example string: $1;1;;;;21,0;;;;;;;;42;;;;;;;;;;;0
    // string format: log view
    // $1;          start symbol
    // 1;           state (always 1)
    // ;            timestamp (not used)
    // 12,0;        temperature sensor 1
    // 12,0;        temperature sensor 2
    // 12,0;        temperature sensor 3
    // 12,0;        temperature sensor 4
    // 12,0;        temperature sensor 5
    // 12,0;        temperature sensor 6
    // 12,0;        temperature sensor 7
    // 12,0;        temperature sensor 8
    // 50;          humidity sensor 1
    // 50;          humidity sensor 2
    // 50;          humidity sensor 3
    // 50;          humidity sensor 4
    // 50;          humidity sensor 5
    // 50;          humidity sensor 7
    // 50;          humidity sensor 8
    // 12,0;        temperature of combined sensor
    // 50;          humidity of combined sensor
    // 100;         wind speed in km/h of combined sensor
    // 120;         rainfall amount of combined sensor
    // 1;           rain state of combined sensor: 1: yes, 0
    // 0<cr><lf>    stop symbol

    std::string str(std::string(reinterpret_cast<char*>(&buf[0]), size));

    str.erase(0, 5);
    std::replace(str.begin(), str.end(), ',', '.');

    while ((k = str.find(";")) != std::string::npos) {
        if (k > 0) {
            values.push_back(std::stof(str));
        } else {
            values.push_back(0.0);
        }
        str.erase(0, k+1);
    }

    for (const auto v: values)
        std::cerr << "val: " << v << std::endl;

}

void DeviceWde1::getSendData(std::vector<uint8_t> &buf, int &size)
{

}

} // namespace villa
