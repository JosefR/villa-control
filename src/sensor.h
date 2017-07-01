#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <chrono>
#include <list>

namespace villa {

class Program;
class Device;

enum class SensorType {
    Thermometer,  // temperature in °C
    Hygrometer,   // air humidity in percent
    RainGauge,    // amount of rain in ml/m²
    RainState,    // if it is raining currently
    Barometer,    // air pressure in Pa
    Anemometer,   // wind speed in km/h
    SmokeDetector,
    CarbonMonoxideDetector
};

class Sensor {
public:
    Sensor(Device *device, SensorType type, const std::string& name);
    Sensor() = delete;
    virtual ~Sensor();

    double value() const;
    void setValue(double value);

    bool active() const;
    void setActive(bool active);

    std::string name() const;
    void setName(const std::string& name);

    std::chrono::system_clock::time_point lastUpdate() const;
    void setLastUpdate(const std::chrono::system_clock::time_point& lastUpdate);

    Device *device() const;

private:
    void notifyListeners();

private:
    Device *mDevice;
    SensorType mType;
    std::string mName;
    bool mActive;
    double mValue;
    std::chrono::system_clock::time_point mLastUpdate;
    std::list<Program*> mListeners;
};

}  // namespace villa

#endif  // SENSOR_H
