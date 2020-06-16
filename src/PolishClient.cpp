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
    callbacks.push_back(this->polishLoop());
}
PolishClient::~PolishClient()
{
    delete tcp;
}
Suspendable PolishClient::polishLoop()
{
    SUSPEND();
    while(1)
    {
        // Read object number
        uint64_t id;
        WAIT_FOR(tcp->Read<uint64_t>(&id));
        if(objects.size() <= id) {
            std::cout << "Attempted to call on undefined object #" << id << std::endl;
        } else {
            WAIT_FOR(objects[id]->Process(this));
        }
    }
}
void PolishClient::Run()
{
    while(1)
    {
        for(auto it=callbacks.begin(); it != callbacks.end(); )
        {
            if(it->done()) {
                // Remove it from array
                std::cout << "REMOVAL" << std::endl;
                std::exit(1);
                callbacks.erase(it);
                break;
            } else {
                it->resume();
                it++;
            }
        }
    }
}