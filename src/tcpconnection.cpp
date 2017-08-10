#include <stdexcept>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <array>
#include <memory>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "tcpclientconnection.h"
#include "tcpconnection.h"

namespace villa {

TcpConnection::TcpConnection(EventManager *evmgr, const char *ip,
    uint16_t port)
    : ServerConnection(evmgr)
{
    int fd = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0);
    if (fd == -1) {
        throw(std::runtime_error(
            std::string("socket() failed").append(strerror(errno))));
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr))
            == -1) {
        std::cerr << "bind() failed: " << strerror(errno) << std::endl;
    }

    if (listen(fd, 32) == -1) {
        std::cerr << "listen() failed: " << strerror(errno) << std::endl;
    }

    mFd = fd;

    mEvMgr->registerConnection(this);
}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::timeout()
{

}

void TcpConnection::read()
{
//    std::array<uint8_t,256> buf;
    int client_fd;
    struct sockaddr_in addr;
    socklen_t len;

    client_fd = accept(mFd, reinterpret_cast<struct sockaddr*>(&addr), &len);
    if (client_fd == -1) {
        std::cerr << "accept failed: " << strerror(errno) << std::endl;
        return;
    }

    std::cout << "new client:  " << client_fd << std::endl;

//    while (1) {
//        ret = recv(mFd, &client_fd, sizeof(client_fd), 0);
//        if (ret == -1) {
//            if (errno == EINTR)
//                continue;
//            if (errno == EAGAIN || errno == EWOULDBLOCK)
//                return;
//            throw(std::runtime_error(strerror(errno)));
//        }

//    }

    auto client = std::make_unique<TcpClientConnection>(mEvMgr, client_fd);

    addClientConnection(std::move(client));
}

void TcpConnection::write()
{

}

int TcpConnection::getFd() const
{
    return mFd;
}

} // namespace villa
