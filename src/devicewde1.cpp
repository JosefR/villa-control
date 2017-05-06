#include <string>
#include <algorithm>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "devicewde1.h"

namespace villa {

DeviceWde1::DeviceWde1(std::map<std::string, std::string>& config)
    : Device(config)
{
    std::cerr << "DeviceWde1::DeviceWde1" << std::endl;

    // add all possible sensors

    std::string name("Sensor X: Temperature");
    for (int i = 0; i < 8; i++) {
        name.replace(7, 1, std::to_string(i));
        mSensors.push_back(
            std::make_shared<Sensor>(SensorType::Thermometer, name));
    }

    name = std::string("Sensor X: Humidity");
    for (int i = 0; i < 8; i++) {
        name.replace(7, 1, std::to_string(i));
        mSensors.push_back(
            std::make_shared<Sensor>(SensorType::Hygrometer, name));
    }

    mSensors.push_back(std::make_shared<Sensor>(
        SensorType::Thermometer, "Combined Sensor: Temperature"));
    mSensors.push_back(std::make_shared<Sensor>(SensorType::Hygrometer,
                                                "Combined Sensor: Humidity"));
    mSensors.push_back(std::make_shared<Sensor>(SensorType::Anemometer,
                                                "Combined Sensor: Wind Speed"));
    mSensors.push_back(std::make_shared<Sensor>(
        SensorType::RainGauge, "Combined Sensor: Rain Amount"));
    mSensors.push_back(std::make_shared<Sensor>(SensorType::RainState,
                                                "Combined Sensor: Rain State"));
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

void DeviceWde1::processReadData(std::vector<uint8_t>& buf, int& size)
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

    auto it = mSensors.begin();
    int i = 0;
    while (((k = str.find(";")) != std::string::npos) && it != mSensors.end()) {
        if (k > 0) {
            values.push_back(std::stof(str));
            (*it)->setValue(std::stof(str));
            (*it)->setActive(true);
        } else {
            values.push_back(0.0);
            (*it)->setActive(false);
        }
        str.erase(0, k + 1);
        it++;
    }

    for (auto s : mSensors) {
        std::cerr << "Sensor (" << (s->active() ? "active) " : "inactive) ")
                  << s->name() << "Value: " << s->value() << std::endl;
    }
}

void DeviceWde1::getSendData(std::vector<uint8_t>& buf, int& size)
{
}

}  // namespace villa
