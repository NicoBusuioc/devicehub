#pragma once
#include "Device.hpp"

class GpioController : public Device {
    public:
        using Device::Device;
        void printDeviceInfo() const override;
};

