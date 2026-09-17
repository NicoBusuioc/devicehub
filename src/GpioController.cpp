#include <iostream>
#include "GpioController.hpp"

void GpioController::printDeviceInfo() const {
    printCommonInfo();
    std::cout << std::endl;
}