#include <iostream>
#include <memory>
#include "Device.hpp"
#include "DeviceManager.hpp"
#include "TemperatureSensor.hpp"
#include "SerialController.hpp"
#include "GpioController.hpp"

int main () {

    DeviceManager deviceManager;
    
    deviceManager.addDevice(std::make_unique<SerialController>("CPU Temperatur", DeviceState::ENABLED));
    deviceManager.addDevice(std::make_unique<GpioController>("GPIO Controller"));
    deviceManager.addDevice(std::make_unique<SerialController>("CAN Controller"));
  
    auto ptr = deviceManager.findDevice(1);
    if(ptr != nullptr) {
        ptr->setConnectionState(ConnectionState::ONLINE);
    }
    deviceManager.printAllDevices();
    std::cout << ("==========================================================================") << std::endl;

    deviceManager.addDevice(std::make_unique<TemperatureSensor> ("Temperature Sensor", 20.));
    ptr = deviceManager.findDevice(3);
    if(ptr != nullptr) {
        ptr->setConnectionState(ConnectionState::ONLINE);
        ptr->setDeviceState(DeviceState::ENABLED);
    }
    deviceManager.printAllDevices();

    std::cout << ("==========================================================================") << std::endl;
    std::cout << "Device count: " << deviceManager.getDeviceCount() << std::endl;
    auto removedDevice = deviceManager.removeDevice(0);
    if (removedDevice.has_value()) {
        std::cout << "from the main: " << removedDevice.value()->getName() << std::endl;
        removedDevice.value()->printDeviceInfo();
    }

    removedDevice = deviceManager.removeDevice(20);
    if (!removedDevice.has_value()) {
        std::cout << "Device with ID: 20 wasn't registered yet!" << std::endl;
    }
    std::cout << "Device count: " << deviceManager.getDeviceCount() << std::endl;
    return 0;
}

