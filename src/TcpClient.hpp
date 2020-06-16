#pragma once
#include <SFML/Network.hpp>
#include "Suspendable.hpp"
class TcpClient
{
    public:
        TcpClient(const sf::IpAddress &remoteAddress, unsigned short remotePort);
        template<typename T>
        Suspendable Read(T*);
        template<typename T>
        Suspendable Write(const T data);
        Suspendable Read(char* output, std::size_t length);
        Suspendable Write(const char* data, std::size_t length);
    private:
        sf::TcpSocket socket;
        const sf::IpAddress &remoteAddress;
        unsigned short remotePort;
};
template<typename T>
Suspendable TcpClient::Read(T* output)
{
    WAIT_FOR(Read((char*)output, sizeof(T)));
}

template<typename T>
Suspendable TcpClient::Write(const T data)
{
    WAIT_FOR(Write((const char*)&data, sizeof(T)));
}