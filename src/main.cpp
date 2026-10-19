#include <iostream>
#include <memory>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <expected>
#include "Device.hpp"
#include "DeviceManager.hpp"
#include "TemperatureSensor.hpp"
#include "SerialController.hpp"
#include "GpioController.hpp"
#include "FileDescriptor.hpp"

namespace OD {  // Open Device Namespace
    std::expected<FileDescriptor, std::error_code> openDevice(const std::string& path) {
        int fd = ::open(path.c_str(), O_RDWR | O_TRUNC);

        if (fd == -1) {
            const int err = errno;
            return std::unexpected(
                std::error_code(err, std::generic_category())
            );
        }

        return FileDescriptor{fd};
    }
}

int main () {

    DeviceManager deviceManager;
    
    deviceManager.addDevice(std::make_unique<SerialController>("CPU Temperatur", DeviceState::ENABLED));
    deviceManager.addDevice(std::make_unique<GpioController>("GPIO Controller"));
    deviceManager.addDevice(std::make_unique<SerialController>("CAN Controller"));
  
    auto ptr = deviceManager.findDevice(1);
    if(ptr != nullptr) {
        ptr->setConnectionState(ConnectionState::ONLINE);
    }
    deviceManager.printAllDevices();
    std::cout << ("==========================================================================") << std::endl;

    deviceManager.addDevice(std::make_unique<TemperatureSensor> ("Temperature Sensor", 20.));
    ptr = deviceManager.findDevice(3);
    if(ptr != nullptr) {
        ptr->setConnectionState(ConnectionState::ONLINE);
        ptr->setDeviceState(DeviceState::ENABLED);
    }
    deviceManager.printAllDevices();

    std::cout << ("==========================================================================") << std::endl;
    std::cout << "Device count: " << deviceManager.getDeviceCount() << std::endl;
    auto removedDevice = deviceManager.removeDevice(0);
    if (removedDevice.has_value()) {
        std::cout << "from the main: " << removedDevice.value()->getName() << std::endl;
        removedDevice.value()->printDeviceInfo();
    }

    removedDevice = deviceManager.removeDevice(20);
    if (!removedDevice.has_value()) {
        std::cout << "Device with ID: 20 wasn't registered yet!" << std::endl;
    }
    std::cout << "Device count: " << deviceManager.getDeviceCount() << std::endl;

    std::cout << ("==========================================================================") << std::endl;
    auto device = deviceManager.findDevice(2);
    if (device != nullptr) {
        device->setConnectionState(ConnectionState::ONLINE);
    }

    const DeviceManager& constDM = deviceManager;
    auto constDevice = constDM.findDevice(2);
    if (constDevice != nullptr) {
        constDevice->printDeviceInfo();
        // constDevice->setConnectionState(ConnectionState::OFFLINE);
        // constDevice->printDeviceInfo();
    }

    auto id = 21;
    device = deviceManager.findDevice(id);
    constDevice = constDM.findDevice(id);
    if ((device == nullptr) && (constDevice == nullptr)) {
        std::cout << "Device with ID: " << id << " wasn't registered yet!" << std::endl;
    }

    std::cout << ("==========================================================================") << std::endl;

    auto result =  OD::openDevice("test.txt");
    if (result.has_value()) {
        std::cout << "Opened Device!" << std::endl;

        const size_t bytes = strlen("Hello from DeviceHub!");
        ssize_t num_bytes = ::write(result.value().getFd(), "Hello from DeviceHub!", bytes);
        if (num_bytes == -1) {
            const int savedErrno = errno;
            std::error_code ec(savedErrno, std::generic_category());
            std::cerr << "Write failed: " << ec.message() << std::endl;
        } else if (static_cast<size_t>(num_bytes) != bytes) {
            std::cerr << "Written only " << num_bytes << " instead of " << bytes << std::endl;
        } else {
            std::cerr << "Data writtten with success!" << std::endl;
        }
    } else {
        std::cout << "unexpected " << result.error() << std::endl;
    }


    return 0;
}
