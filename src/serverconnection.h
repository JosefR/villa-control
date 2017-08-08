#ifndef VILLA_SERVERCONNECTION_H
#define VILLA_SERVERCONNECTION_H

#include <list>
#include <memory>

#include "connection.h"
#include "eventmanager.h"

namespace villa {

class ClientConnection;

class ServerConnection : public Connection
{
public:
    ServerConnection(EventManager *evmgr);
    ServerConnection() = delete;
    virtual ~ServerConnection();
    virtual void timeout() = 0;
    virtual void read() = 0;
    virtual void write() = 0;
    virtual int getFd() const = 0;

protected:
    void addClientConnection(std::unique_ptr<villa::ClientConnection> client);

private:
    std::list<std::unique_ptr<ClientConnection>> mClients;
};

} // namespace villa

#endif // VILLA_SERVERCONNECTION_H
