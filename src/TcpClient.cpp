#include "TcpClient.hpp"
#include <stdexcept>
#include <string.h>
#include <iostream>
TcpClient::TcpClient(const sf::IpAddress &remoteAddress, unsigned short remotePort):remoteAddress(remoteAddress), remotePort(remotePort)
{
    sf::Socket::Status status = socket.connect(remoteAddress, remotePort);
    if(status != sf::Socket::Done)
    {
        throw std::runtime_error("Could not connect to TCP");
    }
}
void TcpClient::Read(char* output, std::size_t length)
{
    std::size_t received;
    sf::Socket::Status status = socket.receive(output, length, received);
    if(status != sf::Socket::Status::Done)
    {
        std::cout << "ERROR" << std::endl;
        switch(status) {
            case sf::Socket::Status::Disconnected:
                throw std::runtime_error("Got disconnected");
            case sf::Socket::Status::Error:
                throw std::runtime_error("Got TCP error");
            case sf::Socket::Status::NotReady:
                throw std::runtime_error("TCP was not ready");
            case sf::Socket::Status::Partial:
                throw std::runtime_error("Got partial");
            default:
                throw std::runtime_error("Unknown socket error");
        }
    }
    if(received != length)
    {
        std::size_t needed = length - received;
        Read(output+received, needed);
    }
}
void TcpClient::Write(const char* data, std::size_t length)
{
    socket.send(data, length);
}
/*
char data[100];
std::size_t received;
while(1) {
    received=0;
    memset(data, 0, 100*sizeof(char));

    socket.receive(data, 100, received);
    std::cout << "Data length: " << received << std::endl;
    std::cout << "Received: '" << data << "'" << std::endl;
}
*/