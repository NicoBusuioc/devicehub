#include <iostream>
#include "Device.hpp"
#include "DeviceManager.hpp"

int main () {

    DeviceManager deviceManager;

    Device device_CputTemp("CPU Temperatur", Status::ENABLED);
    Device device_GPIOController("GPIO Controller");
    Device device_CANController("CAN Controller");

    deviceManager.addDevice(device_CputTemp);
    deviceManager.addDevice(device_GPIOController);
    deviceManager.addDevice(device_CANController);

    std::cout << "Total devices: "  << deviceManager.getDeviceCount() << std::endl;
    deviceManager.printAllDevices();

    std::optional<Device> result1 {deviceManager.findDevice(1)};
    if (result1)
        std::cout << "DEVICE FOUND! " << result1->getName() << std::endl;
    else
        std::cout << "DEVICE NOT FOUND!" << std::endl;

    std::optional<Device> result2 {deviceManager.findDevice(99)};
    if (result2)
        std::cout << "DEVICE FOUND!" << std::endl;
    else
        std::cout << "DEVICE NOT FOUND!" << std::endl;

    return 0;
}

