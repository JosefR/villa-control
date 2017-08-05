#ifndef VILLA_SCTPCONNECTION_H
#define VILLA_SCTPCONNECTION_H

#include "connection.h"

namespace villa {

class SctpConnection : public Connection
{
public:
    SctpConnection(EventManager *evmgr, const char *ip, uint16_t port);

    virtual ~SctpConnection();

    virtual void timeout();
    virtual void read();
    virtual void write();
    virtual int getFd() const;

private:
    int mFd;
};

} // namespace villa

#endif // VILLA_SCTPCONNECTION_H
