#ifndef VILLA_EVENTMANAGER_H
#define VILLA_EVENTMANAGER_H

#include <list>
#include <array>
#include <memory>
#include <mutex>
#include <functional>

#include <sys/epoll.h>

#include "connection.h"

namespace villa {

class EventManager {
   public:
    EventManager();

    void addConnection(std::shared_ptr<Connection> conn);

    void run();

   private:
    //    void addEvent(std::shared_ptr<Device> dev);
    //    void addReadCallback(std::function<void(std::array<uint8_t>)> cb);
    //    void addWriteCallback(std::function<void(std::array<uint8_t>)> cb);

   private:
    int mEpollfd;
    std::map<int, std::shared_ptr<Connection>> mConnections;
    //    std::unique_ptr<event_base, decltype(&event_base_free)> mEvBase;
    std::mutex mMtx;
};

}  // namespace villa

#endif  // VILLA_EVENTMANAGER_H
