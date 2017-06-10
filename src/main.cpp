#include <memory>
#include <stdexcept>
#include <iostream>

#include "eventmanager.h"
#include "connection.h"
#include "internalconnection.h"
#include "ttyconnection.h"
#include "devicewde1.h"
#include "serialport.h"

int main(int argc, char** argv)
{
    villa::EventManager evmgr;

    // TODO: read config file

    std::map<std::string, std::string> device_config{
        {"name", "USB WDE1"}, {"connection", "/dev/ttyUSB0:9600"}};

    villa::InternalConnection internalcon(&evmgr);
    villa::TtyConnection con1(&evmgr, "/dev/ttyUSB0",
                              villa::SerialPort::BaudRate::Baud38400);

    auto dev1(std::make_unique<villa::DeviceWde1>(device_config));
    con1.addDevice(std::move(dev1));

    try {
        evmgr.run();
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown Exception" << std::endl;
        return -1;
    }

    return 0;
}
