#ifndef VILLA_EVENTMANAGER_H
#define VILLA_EVENTMANAGER_H

#include <list>
#include <array>
#include <memory>
#include <mutex>
#include <functional>

#include <sys/epoll.h>

namespace villa {

class EventManager {
public:
    EventManager();

    void registerConnection(void *conn);

    void unregisterConnection(void *conn);

    void run();

    std::list<std::string> getSensors();

private:
    //    void addEvent(std::shared_ptr<Device> dev);
    //    void addReadCallback(std::function<void(std::array<uint8_t>)> cb);
    //    void addWriteCallback(std::function<void(std::array<uint8_t>)> cb);

private:
    int mEpollfd;
    std::mutex mMtx;
};

}  // namespace villa

#endif  // VILLA_EVENTMANAGER_H
