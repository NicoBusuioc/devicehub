#include <iostream>
#include "Device.hpp"
#include "DeviceManager.hpp"
#include "TemperatureSensor.hpp"

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

    TemperatureSensor tempSensor("Temperatur Sensor", 20.);
    std::cout << tempSensor.getName() <<": " << tempSensor.getTemperature() << std::endl;
    tempSensor.setTemperature(23.5);
    std::cout << tempSensor.getName() <<": " << tempSensor.getTemperature() << std::endl;


    // addDevice expects a type of "Device", but we fit here the "TemperatureSensor" type, that is child type of "Device"
    /*  It is called:      Object Slicing
        TemperatureSensor
        ┌───────────────────────┐
        │ Device-Anteil         │  ← wird kopiert
        ├───────────────────────┤
        │ TemperatureSensor-Teil│  ← geht verloren
        └───────────────────────┘

                    ↓

        std::vector<Device>

        ┌───────────────────────┐
        │ Device                │
        └───────────────────────┘   
    */
    deviceManager.addDevice(tempSensor);
    std::cout << "Total devices: "  << deviceManager.getDeviceCount() << std::endl;
    if (true != deviceManager.setDeviceState(3, ConnectionState::ONLINE))
        std::cout << "No such device with ID: " << 3 << std::endl;
    deviceManager.printAllDevices();

    auto tempSens = deviceManager.findDevice(3);
    if (tempSens.has_value()) {
        std::cout << tempSens->getName() << std::endl;
        // std::cout << tempSens->getName() << tempSens->getTemperature() << std::endl;  // error: ‘class Device’ has no member named ‘getTemperature’
    }

    return 0;
}

