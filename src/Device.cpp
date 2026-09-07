#include "Device.hpp"

unsigned int Device::uniq_id = 0;

Device::Device (const std::string& newName, DeviceState newStatus) 
    : id(uniq_id++), name(newName), deviceState(newStatus), connectionState(ConnectionState::OFFLINE) {
}

Device::Device (const std::string& newName) 
    : id(uniq_id++), name(newName), deviceState(DeviceState::DISABLED), connectionState(ConnectionState::OFFLINE) {
}

unsigned int Device::getId() const {
    return id;
}

// we dont want to change the id 
// void Device::setId(unsigned int newId) {
//     id = newId;
// }

const std::string& Device::getName() const {
    return name;
}

void Device::setName(const std::string& newName) {
    name = newName;
}

DeviceState Device::getDeviceState() const {
    return deviceState;
}

void Device::setDeviceState(DeviceState newStatus) {
    deviceState = newStatus;
}

std::string Device::getStringDeviceState() const {
    switch (deviceState)
    {
    case DeviceState::ENABLED:
        return "ENABLED";
    case DeviceState::DISABLED:
        return "DISABLED";
    case DeviceState::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

ConnectionState Device::getConnectionState() const {
    return connectionState;
}

std::string Device::getStringConnectionState() const {
    switch (connectionState)
    {
    case ConnectionState::ONLINE:
        return "ONLINE";
    case ConnectionState::OFFLINE:
        return "OFFLINE";
    default:
        return "UNKNOWN";
    }
}

void Device::setConnectionState(ConnectionState newConnectionState) {
    connectionState = newConnectionState;
}