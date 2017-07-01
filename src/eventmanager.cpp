#include <ctime>
#include <cstring>
#include <algorithm>

#include "connection.h"
#include "eventmanager.h"

namespace villa {

EventManager::EventManager()
{
    mEpollfd = epoll_create1(EPOLL_CLOEXEC);
    if (mEpollfd == -1) {
        throw(std::runtime_error(strerror(errno)));
    }
}

void EventManager::registerConnection(Connection *conn)
{
    std::lock_guard<std::mutex> lock(mMtx);

    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.ptr = conn;
    if (epoll_ctl(mEpollfd, EPOLL_CTL_ADD, conn->getFd(), &ev) == -1) {
        throw(std::runtime_error(
            std::string("epoll_ctl add: ").append(strerror(errno))));
    }
}

void EventManager::unregisterConnection(Connection *conn)
{
    if (epoll_ctl(mEpollfd, EPOLL_CTL_DEL, conn->getFd(), nullptr) == -1) {
        throw(std::runtime_error(
            std::string("epoll_ctl add: ").append(strerror(errno))));
    }
}

void EventManager::registerProgram(Program *prog)
{
    mPrograms.push_back(prog);
}

void EventManager::unregisterProgram(Program *prog)
{
    auto it = std::find(mPrograms.begin(), mPrograms.end(), prog);
    mPrograms.erase(it);
}

void EventManager::registerSensorListener(std::__cxx11::string device, std::string sensor,
    Program *prog)
{
    // TODO
}

void EventManager::run()
{
    const int max_epoll_events = 32;
    struct epoll_event events[max_epoll_events];

    while (1) {
        int nfds = epoll_wait(mEpollfd, events, max_epoll_events, -1);
        if (nfds == -1) {
            throw(std::runtime_error(
                std::string("epoll_wait failed: ").append(strerror(errno))));
        }

        for (int n = 0; n < nfds; ++n) {
            if (events[n].events & EPOLLIN) {
                static_cast<Connection*>(events[n].data.ptr)->read();
            }
        }
    }
}

std::list<std::string> EventManager::getSensors()
{
    std::list<std::string> sensors;

    // TODO
}

}  // namespace villa
