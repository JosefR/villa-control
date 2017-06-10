#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <sys/eventfd.h>
#include <unistd.h>
#include "internalconnection.h"

namespace villa {

InternalConnection::InternalConnection(EventManager *evmgr)
    : Connection(evmgr)
{
    mEventFD = eventfd(0, EFD_NONBLOCK);
    if (mEventFD == -1)
        throw(std::runtime_error(
                std::string("eventfd() failed").append(strerror(errno))));

    mEvMgr->registerConnection(this);
}

InternalConnection::~InternalConnection()
{
    mEvMgr->unregisterConnection(this);

    if (mEventFD != -1)
        close(mEventFD);
}

void InternalConnection::timeout()
{
}

void InternalConnection::read()
{
}

void InternalConnection::write()
{
}

int InternalConnection::getFd() const
{
    return mEventFD;
}

}  // namespace villa
