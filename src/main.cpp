#include <iostream>
#include "Device.hpp"

int main () {

    Device device_CputTemp("CPU Temperatur", Status::ENABLED);
    Device device_GPIOController("GPIO Controller");

    std::cout << device_CputTemp.getName() << " status: " << device_CputTemp.getStringStatus() << " ID: " << device_CputTemp.getId() << std::endl;
    std::cout << device_GPIOController.getName() << " status: " << device_GPIOController.getStringStatus() << " ID: " << device_GPIOController.getId() << std::endl;
    return 0;
}

