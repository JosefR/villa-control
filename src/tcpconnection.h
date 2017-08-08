#ifndef VILLA_SCTPCONNECTION_H
#define VILLA_SCTPCONNECTION_H

#include "serverconnection.h"

namespace villa {

class TcpConnection : public ServerConnection
{
public:
    TcpConnection(EventManager *evmgr, const char *ip, uint16_t port);

    virtual ~TcpConnection();

    virtual void timeout();
    virtual void read();
    virtual void write();
    virtual int getFd() const;

private:
    int mFd;
};

} // namespace villa

#endif // VILLA_SCTPCONNECTION_H
