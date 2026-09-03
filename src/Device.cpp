#include "Device.hpp"

unsigned int Device::uniq_id = 0;

Device::Device (const std::string& newName, Status newStatus) 
    : id(uniq_id++), name(newName), status(newStatus) {
}

Device::Device (const std::string& newName) : id(uniq_id++), name(newName), status(Status::DISABLED) {
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

Status Device::getStatus() const {
    return status;
}

void Device::setStatus(Status newStatus) {
    status = newStatus;
}

std::string Device::getStringStatus() const {
    switch (status)
    {
    case Status::ENABLED:
        return "ENABLED";
    case Status::DISABLED:
        return "DISABLED";
    case Status::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}