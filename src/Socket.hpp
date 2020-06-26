#pragma once
#include "Suspendable.hpp"
#include <sys/socket.h>
class Socket
{
    public:
        Socket(const char* filename);
        template<typename T>
        Suspendable Read(T*);
        template<typename T>
        Suspendable Write(const T data);
        Suspendable Read(char* output, std::size_t length);
        Suspendable Write(const char* data, std::size_t length);
        ~Socket();
    private:
        std::string filename;
};
template<typename T>
Suspendable Socket::Read(T* output)
{
    WAIT_FOR(Read((char*)output, sizeof(T)));
}

template<typename T>
Suspendable Socket::Write(const T data)
{
    WAIT_FOR(Write((const char*)&data, sizeof(T)));
}