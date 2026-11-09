#pragma once
#include <expected>
#include <span>
#include <system_error>

struct WriteAllError {
    std::error_code code;
    std::size_t bytes_written;
};

class FileDescriptor {
    private:
        int fd;
    public:
        FileDescriptor(int newFD);
        ~FileDescriptor();
        FileDescriptor(const FileDescriptor&) = delete;  // copy constructor is not allowed
        FileDescriptor& operator=(const FileDescriptor&) = delete; // copy operator is also not allowed: a = b; // compile error
        FileDescriptor(FileDescriptor&&) noexcept;
        FileDescriptor& operator=(FileDescriptor&&) noexcept;
        int getFd() const;
        bool isFdValid() const;
        std::expected<std::size_t, std::error_code> read(std::span<std::byte> buffer);
        std::expected<std::size_t, std::error_code> write(std::span<const std::byte> buffer);
        std::expected<std::size_t, WriteAllError> writeAll(std::span<const std::byte> buffer);
};
