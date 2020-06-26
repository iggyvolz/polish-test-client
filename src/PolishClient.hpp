#pragma once
#include <SFML/Network.hpp>
#include "Socket.hpp"
#include <vector>
#include <string>
class PolishObject;
class RootConstructor;
class PolishClient
{
    public:
        PolishClient(const std::string filename);
        void Run();
        ~PolishClient();
        Socket* socket;
        std::vector<PolishObject*> objects;
        void AddCallback(const Suspendable& suspendable);
    private:
        std::vector<Suspendable> callbacks;
        std::vector<Suspendable> pendingCallbacks;
        Suspendable polishLoop();
};
