#pragma once
#include "Device.hpp"


class SerialController : public Device {
    public:
        using Device::Device;  // no need to declare own Constructor, if you don't want it.
        void printDeviceInfo() const override;
};
