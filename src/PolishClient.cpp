#include "PolishClient.hpp"
#include "PolishObject.hpp"
#include <stdexcept>
#include <string.h>
#include<iostream>
#include "Root/Root.hpp"
class PolishObject;
PolishClient::PolishClient(const std::string filename)
{
    socket = new Socket(filename);
    objects.push_back(new Root(this, 0));
    callbacks.push_back(this->polishLoop());
}
PolishClient::~PolishClient()
{
    delete socket;
}
Suspendable PolishClient::polishLoop()
{
    SUSPEND();
    while(1)
    {
        // Read object number
        uint64_t id=-1;
        WAIT_FOR(socket->Read<uint64_t>(&id));
        if(objects.size() <= id) {
            std::cout << "Attempted to call on undefined object #" << id << std::endl;
            std::exit(-1);
        } else {
            std::cout << "Call on object " << id << std::endl;
            WAIT_FOR(objects[id]->Process());
        }
    }
}
void PolishClient::Run()
{
    while(1)
    {
        for(auto it=callbacks.begin(); it != callbacks.end(); it++)
        {
            if(!it->done()) it->resume();
        }
        // Add new callbacks as needed
        for(auto it=pendingCallbacks.begin(); it != pendingCallbacks.end(); it++)
        {
            callbacks.push_back(*it);
        }
        pendingCallbacks.clear();
        // TODO cleanup done callbacks
    }
}

void PolishClient::AddCallback(const Suspendable& suspendable)
{
    pendingCallbacks.push_back(suspendable);
}