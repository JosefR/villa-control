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
    int num_read_bytes;

    mSerPort.get()->read(buf, num_read_bytes);
    std::cerr << "TtyConnection::read ";
    for (int i = 0; i < num_read_bytes; i++) {
        std::cerr << std::hex << std::setfill('0') << std::setw(2)
                  << (unsigned int)buf[i] << " ";
    }
    std::cerr << std::endl;

    for (const auto dev : mDevices) {
        dev->processReadData(buf, num_read_bytes);
    }
}

void TtyConnection::write()
{
}

int TtyConnection::getFd() const
{
    return mSerPort.get()->getFd();
}

}  // namespace villa
