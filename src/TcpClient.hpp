#pragma once
#include <SFML/Network.hpp>
class TcpClient
{
    public:
        TcpClient(const sf::IpAddress &remoteAddress, unsigned short remotePort);
        template<typename T>
        T Read();
        template<typename T>
        void Write(const T data);
        void Read(char* output, std::size_t length);
        void Write(const char* data, std::size_t length);
    private:
        sf::TcpSocket socket;
        const sf::IpAddress &remoteAddress;
        unsigned short remotePort;
};

template<typename T>
T TcpClient::Read()
{
    T output;
    Read((char*)&output, sizeof(T));
    return output;
}

template<typename T>
void TcpClient::Write(const T data)
{
    Write((const char*)&data, sizeof(T));
}