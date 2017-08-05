#include <iostream>
#include <cstring>
#include <cerrno>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int epollfd = epoll_create1(0);
    if (epollfd == -1) {
        std::cerr << "epoll_create1() failed" << std::endl;
    }

    //int listenfd = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0);
    int listenfd = socket(AF_INET, SOCK_SEQPACKET|SOCK_NONBLOCK, IPPROTO_SCTP);
    if (listenfd == -1) {
        std::cerr << "socket() failed" << strerror(errno) << std::endl;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(9991);

    if (bind(listenfd, reinterpret_cast<sockaddr*>(&address), sizeof(address))
            == -1) {
        std::cerr << "bind() failed: " << strerror(errno) << std::endl;
    }

    if (listen(listenfd, 32) == -1) {
        std::cerr << "listen() failed: " << strerror(errno) << std::endl;
    }

    epoll_event eev;
    eev.events = EPOLLIN;
    eev.data.fd = listenfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &eev) == -1) {
        std::cerr << "epoll_ctl() failed: " << strerror(errno) << std::endl;
    }

    const int max_epoll_events = 32;
    struct epoll_event events[max_epoll_events];
    char buf[128];

    while (1) {
        int nfds = epoll_wait(epollfd, events, max_epoll_events, -1);
        std::cerr << "epoll unblocked" << std::endl;
        if (nfds == -1) {
            std::cerr << "epoll_wait failed: " << strerror(errno);
        }

        for (int n = 0; n < nfds; ++n) {
            if (events[n].events & EPOLLIN) {
                if (events[n].data.fd == listenfd) {
                    socklen_t size = sizeof(address);
                    int client_fd = accept(listenfd,
                        reinterpret_cast<sockaddr*>(&address), &size);
                    if (client_fd == -1) {
                        std::cerr << "accept failed: " << strerror(errno);
                        return EXIT_FAILURE;
                    }
                    eev.events = EPOLLIN | EPOLLHUP;
                    eev.data.fd = client_fd;
                    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, client_fd, &eev)
                            == -1) {
                        std::cerr << "epoll_ctl() failed: "
                            << strerror(errno) << std::endl;
                        return EXIT_FAILURE;
                    }
                    std::cerr << "added new client" << std::endl;
                    continue;
                }

                int ret;
                if ((ret = recv(events[n].data.fd, buf, 128, 0)) == 0) {
                    std::cerr << "client disconnected" << std::endl;
                    if (epoll_ctl(epollfd, EPOLL_CTL_DEL, events[n].data.fd,
                            nullptr) == -1) {
                        std::cerr << "epoll_ctl() failed: "
                            << strerror(errno) << std::endl;
                        return EXIT_FAILURE;
                    }
                } else {
                    std::cout << "received: " << buf << std::endl;
                }
            } else if (events[n].events & EPOLLHUP) {
                std::cerr << "client disconnected (HUP)" << std::endl;
                if (epoll_ctl(epollfd, EPOLL_CTL_DEL, events[n].data.fd,
                        nullptr) == -1) {
                    std::cerr << "epoll_ctl() failed: "
                        << strerror(errno) << std::endl;
                    return EXIT_FAILURE;
                }
            } else {
                std::cerr << "unexpected event" << std::endl;
            }
        }
    }
    return 0;
}
