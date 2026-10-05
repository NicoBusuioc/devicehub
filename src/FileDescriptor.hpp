#pragma once

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
};
