#include "Socket.hpp"
#include <stdexcept>
#include <string.h>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h> 
#include<unistd.h>
Socket::Socket(const std::string filename):filename(filename)
{
}
Suspendable Socket::Read(char* output, std::size_t length)
{
    while(length != 0)
    {
        int fd = open(filename.c_str(), O_RDONLY | O_NONBLOCK);
        if(fd == -1) {
            throw std::runtime_error("Could not open socket for reading");
        }
        std::size_t received = read(fd, output, length);
        close(fd);
        if(received == -1) {
            throw std::runtime_error("Error while reading data");
        }
        // if(received != 0) std::cout << "Read " << received << std::endl;
        output += received; // Advance pointer by received bytes
        length -= received; // Remove needed bytes from length
        SUSPEND();
    }
    // std::cout << "Done reading" << std::endl;
}
Suspendable Socket::Write(const char* data, std::size_t length)
{
    while(length != 0)
    {
        int fd = open(filename.c_str(), O_WRONLY | O_NONBLOCK);
        if(fd == -1) {
            throw std::runtime_error("Could not open socket for reading");
        }
        std::size_t written = write(fd, data, length);
        close(fd);
        if(written == -1) {
            throw std::runtime_error("Error while writing data");
        }
        data += written;
        length -= written;
        SUSPEND();
    }
}