#include <iostream>
#include "Device.hpp"
#include "DeviceManager.hpp"

int main () {

    DeviceManager deviceManager;

    Device device_CputTemp("CPU Temperatur", DeviceState::ENABLED);
    Device device_GPIOController("GPIO Controller");
    Device device_CANController("CAN Controller");

    deviceManager.addDevice(device_CputTemp);
    deviceManager.addDevice(device_GPIOController);
    deviceManager.addDevice(device_CANController);

    std::cout << "Total devices: "  << deviceManager.getDeviceCount() << std::endl;
    deviceManager.printAllDevices();
    if (true != deviceManager.setDeviceState(1, ConnectionState::ONLINE))
        std::cout << "No such device with ID: " << 1 << std::endl;
    if (true != deviceManager.setDeviceState(3, ConnectionState::ONLINE))
        std::cout << "No such device with ID: " << 3 << std::endl;
    deviceManager.printAllDevices();

    return 0;
}

