#include <iostream>
#include <iomanip>
#include "ttyconnection.h"

namespace villa {

TtyConnection::TtyConnection(std::string path, SerialPort::BaudRate baud)
    : mSerPort(std::make_unique<SerialPort>(path, baud))
{
}

void TtyConnection::timeout()
{
    std::cout << __func__ << std::endl;
}

void TtyConnection::read()
{
    std::vector<uint8_t> buf(128);
    int read_byte;

    mSerPort.get()->read(buf, read_byte);
    std::cerr << __func__ << ": read: ";
    for (int i = 0; i < read_byte; i++)
        std::cerr << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)buf[i] << " ";
    std::cerr << std::endl;

    for (const auto dev : mDevices) {
        /* hand over data */
    }
}


void TtyConnection::write()
{

}

int TtyConnection::getFd() const
{
    return mSerPort.get()->getFd();
}

} // namespace villa
