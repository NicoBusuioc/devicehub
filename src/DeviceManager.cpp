#include <iostream>
#include "DeviceManager.hpp"

/*
Der Vector (std::vector<Device> devices;) speichert Device-Objekte, nicht Device-Referenz
Deshalb kann er nicht einfach die Referenz speichern.

Er erzeugt in seinem eigenen Speicher ein neues Device-Object, indem er den
ursprünglichen Device kopiert
*/
void DeviceManager::addDevice(const Device& device) {
    devices.push_back(device);
}

size_t DeviceManager::getDeviceCount() const {
    return devices.size();
}

void DeviceManager::printAllDevices() const {
    for (const Device& device : devices) {
        std::cout << "ID: " << device.getId() << " | " << device.getName() << " | " << device.getStringStatus() << std::endl;
    }
}

/*
Hier wird  kopie im std::optional<Device> gespeichert
als alternative kann man mit:
std::optional<std::reference_wrapper<const Device>>

aber hier aufpassen mit std::vector, wenn man z.B. ein 
Pushback macht, und Vector realoziert die Daten
dann die Referenz wird nicht mitbezogen und das führt zu einem
Undefined Behavior -> das nennt sich: reference invalidation


optional
   │
   ├── leer
   │
   └── Referenz auf existierendes Device

daher, wenn du später auf Device über std::optional 
zugreifen willst, verwendet man pointer (->), siehe:
main.c line 22
*/
std::optional<Device> DeviceManager::findDevice(unsigned int id) const{
    for (const Device& device : devices) {
        if(id == device.getId())
            return device;
    }
    return {};
}