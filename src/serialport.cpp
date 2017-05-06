#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cerrno>

#include "serialport.h"

namespace villa {

SerialPort::SerialPort() : mFd(-1), mBaud(BaudRate::BaudUndefined)
{
    std::cerr << "SerialPort::SerialPort" << std::endl;
}

SerialPort::SerialPort(const std::string path, SerialPort::BaudRate baud)
{
    std::cerr << "SerialPort::SerialPort" << std::endl;

    mFd = open(path.c_str(), O_RDWR | O_NOCTTY | O_SYNC);

    if (mFd == -1)
        throw std::runtime_error(std::strerror(errno));

    termios tty{0};
    if (tcgetattr(mFd, &tty) != 0) {
        close(mFd);
        mFd = -1;
        throw std::runtime_error("open failed");
    }

    cfsetospeed(&tty, static_cast<int>(baud));
    cfsetispeed(&tty, static_cast<int>(baud));

    tty.c_cc[VMIN] = 0;    // read doesn't block
    tty.c_cc[VTIME] = 10;  // no read timeout

    // set to raw mode
    tty.c_iflag &=
        ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_oflag &= ~OPOST;
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_cflag &= ~(CSIZE | PARENB);
    tty.c_cflag |= CS8;

    // no flow control
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag &= ~CRTSCTS;

    // ignore modem controls
    tty.c_cflag |= (CLOCAL | CREAD);

    // no parity
    tty.c_cflag &= ~(PARENB | PARODD);

    // 1 stop bit, not two
    tty.c_cflag &= ~CSTOPB;

    if (tcsetattr(mFd, TCSANOW, &tty) != 0) {
        close(mFd);
        mFd = -1;
        throw std::runtime_error("open failed");
    }
}

SerialPort::~SerialPort()
{
    std::cerr << "SerialPort::~SerialPort" << std::endl;
    if (mFd > 1)
        close(mFd);
}

SerialPort::BaudRate SerialPort::BaudFromInt(int baud)
{
    switch (baud) {
    case 9600:
        return BaudRate::Baud9600;
    case 115200:
        return BaudRate::Baud115200;
    case 1000000:
        return BaudRate::Baud1000000;
    default:
        throw(std::runtime_error("invalid baud rate"));
    }
}

int SerialPort::getFd() const
{
    return mFd;
}

SerialPort::BaudRate SerialPort::getBaud() const
{
    return mBaud;
}

std::string SerialPort::getPath() const
{
    return mPath;
}

Connection::IOState SerialPort::read(std::vector<uint8_t>& buf, int& read_bytes)
{
    int cnt = buf.size();
    int ret;
    read_bytes = 0;

    while (true) {
        ret = ::read(mFd, &buf[read_bytes], cnt - read_bytes);
        if (ret == 0) {
            return Connection::IOState::FINISHED;
        } else if (ret < 0) {
            throw(std::runtime_error("read failed"));
        } else if (ret == cnt) {
            read_bytes += ret;
            return Connection::IOState::FINISHED;
        } else if (ret < cnt) {
            read_bytes += ret;
            cnt -= ret;
        }
    }
}

}  // namespace villa
