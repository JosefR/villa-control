#include <ctime>
#include <cstring>
#include "eventmanager.h"

namespace villa {

EventManager::EventManager()
{
    mEpollfd = epoll_create1(EPOLL_CLOEXEC);
    if (mEpollfd == -1) {
        throw(std::runtime_error(strerror(errno)));
    }
}

void EventManager::addConnection(std::shared_ptr<Connection> conn)
{
    std::lock_guard<std::mutex> lock(mMtx);

    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = conn->getFd();
    if (epoll_ctl(mEpollfd, EPOLL_CTL_ADD, conn->getFd(), &ev) == -1) {
        throw(std::runtime_error(
            std::string("epoll_ctl add: ").append(strerror(errno))));
    }

    mConnections[conn->getFd()] = conn;
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
            auto conn = mConnections.find(events[n].data.fd);
            if (conn != mConnections.end()) {
                if (events[n].events & EPOLLIN) {
                    conn->second->read();
                }
            }
        }
    }
}

}  // namespace villa
