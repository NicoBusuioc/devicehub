#include <iostream>
#include "SerialController.hpp"


void SerialController::printDeviceInfo() const {
    printCommonInfo();
    std::cout << std::endl;
}