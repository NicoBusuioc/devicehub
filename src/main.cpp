#include <iostream>
#include <memory>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <expected>
#include <array>
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

        // Write Data
        std::string my_data{"Hello from DeviceHub!"};
        std::span view{my_data};
        auto bytes_written = result.value().write(std::as_bytes(view));

        if(bytes_written.has_value()) {
            std::cout << "Bytes written: " << bytes_written.value() << " bytes" << std::endl;
            if (bytes_written.value() != my_data.size()) {
                std::cerr << "Partial write!" << '\n';
                return 1;
            }
        } else {
            std::cerr << "Write failed: " << bytes_written.error().message() << std::endl;
            return 1;
        }

        // Set position to zero
        if (::lseek(result.value().getFd(), 0, SEEK_SET) == -1) {
            const int savedErrno = errno;
            std::error_code ec(savedErrno, std::generic_category());
            std::cerr << "lseek failed: " << ec.message() << '\n';
            return 1;
        }

        // Read Data
        std::array<std::byte, 100> buffer {};
        auto bytes_read = result.value().read(buffer);
        if (bytes_read.has_value()) {
            std::cout << "Bytes read: " << bytes_read.value() << '\n';
        } else {
            std::cerr << "Read failed: " << bytes_read.error().message() << '\n';
            return 1;
        }

        // Check Data write vs read
        if (bytes_written.value() != bytes_read.value()) {
            std::cerr << "Data mismatch!" << std::endl;
            return 1;
        }
        auto wr_data = std::as_bytes(view);
        for(size_t i=0; i<wr_data.size(); ++i) {
            if(wr_data[i] != buffer[i]) {
                std::cerr << "Data mismatch!" << std::endl;
                return 1;
            }
        }

        std::cout << "Data is identically" << std::endl;
        
    } else {
        std::cout << "unexpected " << result.error() << std::endl;
    }

    return 0;
}
