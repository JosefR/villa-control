#ifndef VILLA_UDSSERVERCONNECTION_H
#define VILLA_UDSSERVERCONNECTION_H

#include "connection.h"

namespace villa {

class UdsServerConnection : public Connection
{
public:
    UdsServerConnection(EventManager *evmgr);

    virtual ~UdsServerConnection();

    virtual void timeout();
    virtual void read();
    virtual void write();

    virtual int getFd() const;
};

} // namespace villa

#endif // VILLA_UDSSERVERCONNECTION_H
