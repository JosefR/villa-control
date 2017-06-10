#ifndef INTERNALCONNECTION_H
#define INTERNALCONNECTION_H

#include <memory>

#include "connection.h"

namespace villa {

class InternalConnection : public Connection {
public:
    InternalConnection(EventManager *evmgr);
    virtual ~InternalConnection();

    virtual void timeout();
    virtual void read();
    virtual void write();

    virtual int getFd() const;

private:
    int mEventFD;
};

}  // namespace villa

#endif  // INTERNALCONNECTION_H
