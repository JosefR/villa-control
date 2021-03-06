#include "program.h"
#include "sensor.h"

namespace villa {
Sensor::Sensor(Device *device, SensorType type, const std::string& name)
    : mDevice(device), mType(type), mName(name), mActive(false), mValue(0.0)
{
}

Sensor::~Sensor()
{
}

double Sensor::value() const
{
    return mValue;
}

void Sensor::setValue(double value)
{
    mValue = value;
}

bool Sensor::active() const
{
    return mActive;
}

void Sensor::setActive(bool active)
{
    mActive = active;
}

std::string Sensor::name() const
{
    return mName;
}

void Sensor::setName(const std::string& name)
{
    mName = name;
}

std::chrono::system_clock::time_point Sensor::lastUpdate() const
{
    return mLastUpdate;
}

void Sensor::setLastUpdate(
    const std::chrono::system_clock::time_point& lastUpdate)
{
    mLastUpdate = lastUpdate;
}

Device *Sensor::device() const
{
    return mDevice;
}

void Sensor::notifyListeners()
{
    for (auto l: mListeners) {
        l->eventCallback(this);
    }
}
}
