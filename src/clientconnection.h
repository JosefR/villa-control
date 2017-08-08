#ifndef VILLA_CLIENTCONNECTION_H
#define VILLA_CLIENTCONNECTION_H

#include "eventmanager.h"
#include "connection.h"

namespace villa {

class ClientConnection : public Connection
{
public:
    ClientConnection(EventManager *evmgr);
    ClientConnection() = delete;
    virtual ~ClientConnection();
    virtual void timeout() = 0;
    virtual void read() = 0;
    virtual void write() = 0;
    virtual int getFd() const = 0;
};

} // namespace villa

#endif // VILLA_CLIENTCONNECTION_H
