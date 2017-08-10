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
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1) {
        std::cerr << "socket() failed" << strerror(errno) << std::endl;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9991);

    if (connect(clientfd, reinterpret_cast<struct sockaddr*>(&address),
            sizeof(address)) == -1) {
        if (errno != EINPROGRESS) {
            std::cerr << "connect() failed: " << strerror(errno) << std::endl;
            return EXIT_FAILURE;
        }
    }

    while (1) {
        send(clientfd, "test", 5, 0);
        sleep(5);
    }

    close(clientfd);
    return 0;
}
