#pragma once
#include <SFML/Network.hpp>
#include "TcpClient.hpp"
#include <vector>
#include <string>
class PolishObject;
class RootConstructor;
class PolishClient
{
    public:
        PolishClient(const sf::IpAddress &remoteAddress, unsigned short remotePort);
        void Run();
        ~PolishClient();
        TcpClient* tcp;
        std::vector<PolishObject*> objects;
    private:
        std::vector<Suspendable> callbacks;
        Suspendable polishLoop();
};

// const std::unordered_map<std::string, void(*)(const TcpClient*)> PolishClient::functions = {
//     {{1,2,3}, PolishClient::testFn}
// };