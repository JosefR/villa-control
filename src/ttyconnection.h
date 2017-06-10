#ifndef VILLA_TTYCONNECTION_H
#define VILLA_TTYCONNECTION_H

#include <memory>
#include <string>

#include "eventmanager.h"
#include "connection.h"
#include "serialport.h"

namespace villa {

class TtyConnection : public Connection {
public:
    TtyConnection(EventManager* evmgr, std::string path,
                  SerialPort::BaudRate baud);

    virtual void timeout();
    virtual void read();
    virtual void write();

    virtual int getFd() const;

private:
    std::unique_ptr<SerialPort> mSerPort;
};

}  // namespace villa

#endif  // VILLA_TTYCONNECTION_H
