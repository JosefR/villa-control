#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <sys/un.h>
#include "udsconnection.h"

namespace villa {

UdsConnection::UdsConnection(EventManager *evmgr, const char *name)
    : Connection(evmgr)
{
    int fd = socket(AF_UNIX, SOCK_STREAM|SOCK_NONBLOCK, 0);

    if (fd == -1) {
        throw(std::runtime_error(
            std::string("socket() failed").append(strerror(errno))));
    }

    // TODO

    mEvMgr->registerConnection(this);
}

UdsConnection::~UdsConnection()
{

}

void UdsConnection::timeout()
{

}

void UdsConnection::read()
{

}

void UdsConnection::write()
{

}

int UdsConnection::getFd() const
{

}

} // namespace villa
