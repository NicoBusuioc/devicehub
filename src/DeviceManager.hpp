#pragma once
#include <vector>
#include <memory>
#include <optional>
#include "Device.hpp"

class DeviceManager
{
    private:
        std::vector<std::unique_ptr<Device>> devices;
    public:
        void addDevice(std::unique_ptr<Device> device);
        size_t getDeviceCount() const;
        void printAllDevices() const;
        Device* findDevice(unsigned int id);
        bool setDeviceState(unsigned int id, ConnectionState state);
};

