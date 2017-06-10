#ifndef VILLA_UDSCONNECTION_H
#define VILLA_UDSCONNECTION_H

#include "connection.h"

namespace villa {

class UdsConnection : public Connection
{
public:
    UdsConnection(EventManager *evmgr);

    virtual ~UdsConnection();

    virtual void timeout();
    virtual void read();
    virtual void write();

    virtual int getFd() const;
};

} // namespace villa

#endif // VILLA_UDSCONNECTION_H
