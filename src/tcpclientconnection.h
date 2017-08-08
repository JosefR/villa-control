#ifndef SCTPCLIENTCONNECTION_H
#define SCTPCLIENTCONNECTION_H

#include "clientconnection.h"
#include "eventmanager.h"

namespace villa {

/**
 * @brief The SctpClientConnection class implements a server-side connection to
 * a SCTP client.
 */
class TcpClientConnection : public ClientConnection
{
public:
    TcpClientConnection(EventManager *evmgr, int fd);
    virtual ~TcpClientConnection();
    virtual void timeout();
    virtual void read();
    virtual void write();
    virtual int getFd() const;

private:
    int mFd;
};

} // namespace villa

#endif // SCTPCLIENTCONNECTION_H
