#include <array>
#include <cstdint>
#include <stdexcept>
#include <cstring>
#include <cerrno>

#include <sys/types.h>
#include <sys/socket.h>

#include "tcpclientconnection.h"

namespace villa {

TcpClientConnection::TcpClientConnection(EventManager *evmgr, int fd)
    : ClientConnection(evmgr), mFd(fd)
{
    mEvMgr->registerConnection(this);
}

TcpClientConnection::~TcpClientConnection()
{

}

void TcpClientConnection::timeout()
{

}

void TcpClientConnection::read()
{
    int ret;
    std::array<uint8_t,256> buf;

    do {
        ret = recv(mFd, buf.data(), buf.size(), 0);
    } while (ret == -1 && errno == EINTR);

    if (ret == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return;
        throw(std::runtime_error(std::string("recv(): ") + strerror(errno)));
    }

    if (ret == 0) {
        // close the connection
        std::cout << "close connection to client " << mFd << std::endl;
        mEvMgr->unregisterConnection(this);
        delete this;
        return;
    }
    std::cout << "received " << ret << " bytes" << std::endl;
}

void TcpClientConnection::write()
{

}

int TcpClientConnection::getFd() const
{
    return mFd;
}

} // namespace villa
