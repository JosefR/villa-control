#include "clientconnection.h"
#include "serverconnection.h"

namespace villa {

ServerConnection::ServerConnection(EventManager *evmgr)
    : Connection(evmgr)
{

}

ServerConnection::~ServerConnection()
{

}

void ServerConnection::addClientConnection(
    std::unique_ptr<ClientConnection> client)
{
    mClients.push_back(std::move(client));
}

} // namespace villa
