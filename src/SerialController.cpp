#include <iostream>
#include "SerialController.hpp"


void SerialController::printDeviceInfo() const {
    printCommonInfo();
    std::cout << std::endl;
}

 SerialController::~SerialController() {
    std::cout << this->getName() << " destructed!" << std::endl;
 }