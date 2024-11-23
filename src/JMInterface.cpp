#include <JMInterface.hpp>


Interface::Interface(HardwareSerial *serial)
{
    this->iSerial = serial;
}

Interface::~Interface()
{
}


