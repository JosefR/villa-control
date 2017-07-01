#ifndef VILLA_EVENTMANAGER_H
#define VILLA_EVENTMANAGER_H

#include <list>
#include <array>
#include <memory>
#include <mutex>
#include <functional>

#include <sys/epoll.h>

#include "program.h"

namespace villa {

class Connection;

class EventManager {
public:
    EventManager();

    void registerConnection(Connection *conn);

    void unregisterConnection(Connection *conn);

    void registerProgram(Program *prog);
    void unregisterProgram(Program *prog);

    void registerSensorListener(std::string device, std::string sensor, Program *prog);

    void run();

    std::list<std::string> getSensors();

private:
    //    void addEvent(std::shared_ptr<Device> dev);
    //    void addReadCallback(std::function<void(std::array<uint8_t>)> cb);
    //    void addWriteCallback(std::function<void(std::array<uint8_t>)> cb);

private:
    int mEpollfd;
    std::mutex mMtx;
    std::list<Program*> mPrograms;
};

}  // namespace villa

#endif  // VILLA_EVENTMANAGER_H
