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
    socket.setBlocking(false);
}
Suspendable TcpClient::Read(char* output, std::size_t length)
{
    std::size_t received;
    sf::Socket::Status status;
    std::cout << "Want to read " << length << std::endl;
    do
    {
        received = 0;
        status = socket.receive(output, length, received);
        switch(status) {
            case sf::Socket::Status::Disconnected:
                std::cout << "Got disconnected" << std::endl;
                break;
                throw std::runtime_error("Got disconnected");
            case sf::Socket::Status::Error:
                throw std::runtime_error("Got TCP error");
            case sf::Socket::Status::NotReady:
                break;
            case sf::Socket::Status::Done:
                break;
            default:
                throw std::runtime_error("Unknown socket error");
        }
        if(received != 0) std::cout << "Read " << received << std::endl;
        output += received; // Advance pointer by received bytes
        length -= received; // Remove needed bytes from length
        SUSPEND();
    } while(received != length);
    std::cout << "Done reading" << std::endl;
}
Suspendable TcpClient::Write(const char* data, std::size_t length)
{
    sf::Packet packet;
    packet.append(data, length);
    sf::Socket::Status status;
    do
    {
        socket.send(packet);
        switch(status) {
            case sf::Socket::Status::Disconnected:
                throw std::runtime_error("Got disconnected");
            case sf::Socket::Status::Error:
                throw std::runtime_error("Got TCP error");
            case sf::Socket::Status::NotReady:
                throw std::runtime_error("TCP was not ready");
            case sf::Socket::Status::Done:
                break;
            case sf::Socket::Status::Partial:
                SUSPEND();
                break;
            default:
                throw std::runtime_error("Unknown socket error");
        }
    } while (status == sf::Socket::Status::Partial);
}