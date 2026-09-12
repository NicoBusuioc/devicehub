#include "TemperatureSensor.hpp"


TemperatureSensor::TemperatureSensor(const std::string& newName, DeviceState newStatus, float newTemperature) : \
                                    Device(newName, newStatus), temperature(newTemperature) {

}

TemperatureSensor::TemperatureSensor(const std::string& newName, float newTemperature) : \
                                    Device(newName), temperature(newTemperature) {

}

float TemperatureSensor::getTemperature() const {
    return temperature;
}

void TemperatureSensor::setTemperature(float newTemperature) {
    temperature = newTemperature;
}