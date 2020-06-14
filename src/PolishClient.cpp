#include "PolishClient.hpp"
#include "PolishObject.hpp"
#include <stdexcept>
#include <string.h>
#include<iostream>
#include "RootConstructor/RootConstructor.hpp"
class PolishObject;
PolishClient::PolishClient(const sf::IpAddress &remoteAddress, unsigned short remotePort)
{
    tcp = new TcpClient(remoteAddress, remotePort);
    objects.push_back(new RootConstructor());
}
PolishClient::~PolishClient()
{
    delete tcp;
}
void PolishClient::Run()
{
    while(1)
    {
        // Read object number
        std::size_t id = tcp->Read<uint64_t>();
        if(objects.size() <= id) {
            std::cout << "Attempted to call on undefined object #" << id << std::endl;
        } else {
            objects[id]->Process(this);
        }
    }
}