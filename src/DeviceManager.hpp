#pragma once
#include <vector>
#include <optional>
#include "Device.hpp"

class DeviceManager
{
    private:
        std::vector<Device> devices;
    public:
        void addDevice(const Device& device);
        size_t getDeviceCount() const;
        void printAllDevices() const;
        std::optional<Device> findDevice(unsigned int id) const;
};

