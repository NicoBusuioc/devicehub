#include <unistd.h>
#include "FileDescriptor.hpp"



FileDescriptor::FileDescriptor(int newFD) : fd(( newFD >= 0 ) ? newFD : -1) {
}

FileDescriptor::~FileDescriptor() {
    if(fd >= 0) {
        ::close(fd);  
    }
}

/*
FileDescriptor a{5};
FileDescriptor b{std::move(a)};

b existiert noch nicht. Ein neues Object wird erzeugt.
*/
FileDescriptor::FileDescriptor(FileDescriptor&& other)noexcept \
                                                : fd(other.fd) {
    other.fd = -1;
}

/*
FileDescriptor a{5};
FileDescriptor b{8};

b = std::move(a);
b existiert bereits. Es wird kein neues Objekt konstruiert, sondern ein bestehendes zugewiesen.
*/
FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) noexcept {
    if(this != &other) { // it excludes b = std::move(b);
        if(fd >= 0) {
            ::close(fd);  
        }
        fd = other.fd;
        other.fd = -1;
    }
    return *this;
}

int FileDescriptor::getFd() const {
    return fd;
}


bool FileDescriptor::isFdValid() const {
    return fd >= 0;
}
