#include <memory>
#include <stdexcept>
#include <iostream>

#include "eventmanager.h"
#include "connection.h"
#include "internalconnection.h"
#include "ttyconnection.h"
#include "tcpconnection.h"
#include "devicewde1.h"
#include "serialport.h"
#include "program.h"

class TestProgram : public villa::Program
{
public:
    TestProgram(villa::EventManager *evmgr)
        : villa::Program(evmgr)
    {
        evmgr->registerSensorListener("USB WDE1", "Sensor 3: Temperature", this);                                                                                 ;
    }

    virtual void eventCallback(villa::Sensor *s)
    {
        if (s->device()->name() == "USB WDE1") {
            if (s->name() == "Sensor 3: Temperature") {
                std::cout << s->device()->name() << ": Sensor 3 updated to " <<
                    s->value() << "°C" << std::endl;
            }
        }
    }

};

int main(int argc, char** argv)
{
    villa::EventManager evmgr;

    // TODO: read config file

    std::map<std::string, std::string> device_config{
        {"name", "USB WDE1"}, {"connection", "/dev/ttyUSB0:9600"}};

    villa::InternalConnection internalcon(&evmgr);
//    villa::TtyConnection con1(&evmgr, "/dev/ttyUSB0",
//                              villa::SerialPort::BaudRate::Baud38400);

//    auto dev1(std::make_unique<villa::DeviceWde1>(device_config));
//    con1.addDevice(std::move(dev1));
    villa::TcpConnection tcpconn(&evmgr, "0.0.0.0", 9991);

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
