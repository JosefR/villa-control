#include <stdexcept>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <array>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "sctpconnection.h"

namespace villa {

SctpConnection::SctpConnection(EventManager *evmgr, const char *ip,
    uint16_t port)
    : Connection(evmgr)
{
    int fd = socket(AF_INET, SOCK_SEQPACKET|SOCK_NONBLOCK, IPPROTO_SCTP);
    if (fd == -1) {
        throw(std::runtime_error(
            std::string("socket() failed").append(strerror(errno))));
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    if (connect(fd, reinterpret_cast<struct sockaddr*>(&addr),
            sizeof(addr)) == -1) {
        close(fd);
        throw(std::runtime_error(
            std::string("connect() failed").append(strerror(errno))));
    }

    mFd = fd;

    mEvMgr->registerConnection(this);
}

SctpConnection::~SctpConnection()
{

}

void SctpConnection::timeout()
{

}

void SctpConnection::read()
{
    int ret;
    std::array<uint8_t,256> buf;

    while (1) {
        ret = recv(mFd, buf.data(), buf.size(), 0);
        if (ret == -1) {
            if (errno == EINTR)
                continue;
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return;
            throw(std::runtime_error(strerror(errno)));
        }
        std::cout << "read " << ret << "bytes" << std::endl;
    }

}

void SctpConnection::write()
{

}

int SctpConnection::getFd() const
{
    return mFd;
}

} // namespace villa
