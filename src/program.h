#ifndef PROGRAM_H
#define PROGRAM_H

#include "sensor.h"

namespace villa {

class EventManager;

class Program
{
public:
    Program(EventManager *evmgr);
    Program() = delete;

    virtual ~Program();

    ///
    /// \brief notifies a program over an updated sensor, that it has subscribed
    /// to
    /// \param s
    ///
    virtual void eventCallback(Sensor *s) = 0;
};

} // namespace villa

#endif // PROGRAM_H
