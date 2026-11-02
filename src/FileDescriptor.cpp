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

std::expected<std::size_t, std::error_code> FileDescriptor::read(std::span<std::byte> buffer) {
    ssize_t read_bytes = ::read(fd, buffer.data(), buffer.size());

    if (read_bytes == -1) {
        const int err = errno;
        return std::unexpected(
            std::error_code(err, std::generic_category())
        );
    }

    return static_cast<std::size_t>(read_bytes);
}


std::expected<std::size_t, std::error_code> FileDescriptor::write(std::span<const std::byte> buffer) {
    
    ssize_t written_bytes = ::write(fd, buffer.data(), buffer.size());

    if (written_bytes == -1) {
        const int err = errno;
        return std::unexpected(
            std::error_code(err, std::generic_category())
        );
    }

    return static_cast<std::size_t>(written_bytes);
}