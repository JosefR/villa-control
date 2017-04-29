#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>
#include <vector>
#include <stdint.h>
#include <termios.h>

#include "connection.h"

namespace villa {

class SerialPort
{
public:
    enum class BaudRate : int {
        BaudUndefined = -1,
        Baud0 = B0,
        Baud50 = B50,
        Baud75 = B75,
        Baud110 = B110,
        Baud134 = B134,
        Baud150 = B150,
        Baud200 = B200,
        Baud300 = B300,
        Baud600 = B600,
        Baud1200 = B1200,
        Baud1800 = B1800,
        Baud2400 = B2400,
        Baud4800 = B4800,
        Baud9600 = B9600,
        Baud19200 = B19200,
        Baud38400 = B38400,
        Baud57600 = B57600,
        Baud115200 = B115200,
        Baud230400 = B230400,
        Baud460800 = B460800,
        Baud500000 = B500000,
        Baud576000 = B576000,
        Baud921600 = B921600,
        Baud1000000 = B1000000,
        Baud1152000 = B1152000,
        Baud1500000 = B1500000,
        Baud2000000 = B2000000,
        Baud2500000 = B2500000,
        Baud3000000 = B3000000,
        Baud3500000 = B3500000,
        Baud4000000 = B4000000
    };

public:
    SerialPort();
    SerialPort(const std::string path, BaudRate baud);
    virtual ~SerialPort();

    static BaudRate BaudFromInt(int baud);

    int getFd() const;
    BaudRate getBaud() const;
    std::string getPath() const;

    Connection::IOState read(std::vector<uint8_t> &buf, int &read_bytes);

private:
    std::string mPath;
    int mFd;
    BaudRate mBaud;
};

} // namespace villa

#endif // SERIALPORT_H
