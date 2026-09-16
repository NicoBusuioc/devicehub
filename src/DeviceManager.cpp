#include "DeviceManager.hpp"

/*
this function receives an uniq_ptr and in order to move give the ownership of the pointer
to the vector, we need to use std::move. 
But why? so as the name says, it is an uniq_ptr, i.e. the can be only one instance. 
Puting this pointer in a function, it will be called by value -> will try to make a copy of it -> it cann't work
That's why we are not copying, but moving it - that is allowed.
*/
void DeviceManager::addDevice(std::unique_ptr<Device> device) {
    devices.push_back(std::move(device));
}

size_t DeviceManager::getDeviceCount() const {
    return devices.size();
}

void DeviceManager::printAllDevices() const {
    for (const auto& device : devices) {
        device->printDeviceInfo();
    }
}

/*
the trick here is, each element of the vector has a container "smart pointer" uniq_pointer, 
but it doesn't mean, we cann not use a Raw Pointer, so that is what we are doing.
Once we found the Uniq_ptr -> we are getting than the Raw pointer of it! 
*/
Device* DeviceManager::findDevice(unsigned int id) {
    for (const auto& device : devices) {
        if(id == device->getId())
            return device.get(); // return the Raw Pointer
    }
    return nullptr;
}

bool DeviceManager::setDeviceState(unsigned int id, ConnectionState state) {
    for (auto& device : devices) {
        if(id == device->getId()) {
            device->setConnectionState(state);
            return true;
        }
    }

    return false;
}