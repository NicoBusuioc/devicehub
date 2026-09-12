#pragma once
#include "Device.hpp"

class TemperatureSensor : public Device {
    private:
        float temperature;
    public:
        TemperatureSensor(const std::string& newName, DeviceState newStatus, float newTemperature);
        TemperatureSensor(const std::string& newName, float newTemperature);
        float getTemperature() const;
        void setTemperature(float newTemperature);
};

