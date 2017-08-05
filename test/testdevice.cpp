#include <iostream>
#include <cstring>
#include <cerrno>
#include <ctime>
#include <stdexcept>

#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/timerfd.h>
#include <arpa/inet.h>

using namespace std;


int main()
{
    int epollfd = epoll_create1(0);
    if (epollfd == -1) {
        std::cerr << "epoll_create1() failed" << std::endl;
    }

    //int listenfd = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0);
    int clientfd = socket(AF_INET, SOCK_SEQPACKET|SOCK_NONBLOCK, IPPROTO_SCTP);
    if (clientfd == -1) {
        std::cerr << "socket() failed" << strerror(errno) << std::endl;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9991);

    if (connect(clientfd, reinterpret_cast<struct sockaddr*>(&address),
            sizeof(address)) == -1) {
        std::cerr << "connect() failed: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    epoll_event eev;
    eev.events = EPOLLIN;
    eev.data.fd = clientfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, clientfd, &eev) == -1) {
        std::cerr << "epoll_ctl() failed: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }


    // create periodic 10 second timer

    static int timerfd = -1;

    if (timerfd = timerfd_create(CLOCK_BOOTTIME, TFD_NONBLOCK) == -1) {
        std::cerr << "timefd_create() failed: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    eev.data.fd = timerfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, clientfd, &eev) == -1) {
        std::cerr << "epoll_ctl() failed: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    struct itimerspec its = {};
    its.it_value.tv_sec = 10;
    its.it_interval.tv_sec = 10;

    if (timerfd_settime(timerfd, 0, &its, nullptr) == -1) {
        std::cerr << "timefd_settime() failed: " << strerror(errno)
            << std::endl;
        return -1;
    }


    // epoll loop

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
                if (events[n].data.fd == clientfd) {
                    int ret;
                    ret = recv(clientfd, buf, sizeof(buf), 0);
                    if (ret == -1) {
                        if (errno != EAGAIN && errno != EWOULDBLOCK &&
                                errno != EINTR) {
                            std::cerr << "recv failed" << std::endl;
                            return EXIT_FAILURE;
                        }
                    } else {
                        std::cout << "received: %d bytes" << ret << std::endl;
                    }
                } else if (events[n].data.fd == timerfd) {
                    std::cout << "timer expired" << std::endl;
                    uint64_t s;
                    int ret = read(timerfd, &s, sizeof(uint64_t));
                    if (ret != sizeof(uint64_t)) {
                        std::cerr << "timer read() failed" << std::endl;
                        return EXIT_FAILURE;
                    }
                }
            } else {
                std::cerr << "unexpected event" << std::endl;
            }
        }
    }
    return 0;
}
