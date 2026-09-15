#include <iostream>
#include <memory>
#include "Device.hpp"
#include "DeviceManager.hpp"
#include "TemperatureSensor.hpp"

int main () {

    DeviceManager deviceManager;
    
    deviceManager.addDevice(std::make_unique<Device>("CPU Temperatur", DeviceState::ENABLED));
    deviceManager.addDevice(std::make_unique<Device>("GPIO Controller"));
    deviceManager.addDevice(std::make_unique<Device>("CAN Controller"));
    deviceManager.printAllDevices();
    auto ptr = deviceManager.findDevice(1);
    if(ptr != nullptr) {
        ptr->setConnectionState(ConnectionState::ONLINE);
    }
    deviceManager.printAllDevices();
    std::cout << ("==========================================================================") << std::endl;

    deviceManager.addDevice(std::make_unique<TemperatureSensor> ("Temperature Sensor", 20.));
    deviceManager.printAllDevices();
    ptr = deviceManager.findDevice(3);
    if (ptr != nullptr) { // is raw pointer valid?
        auto pTempSensor = dynamic_cast<TemperatureSensor*>(ptr); // try to cast it into the object it really is, but use the c++ cast -> it is a runtime check wheter this pointer can be converted
        if (pTempSensor) {
            std::cout << pTempSensor->getTemperature() << std::endl;
        }
    }

    return 0;
}

