#pragma once
#include <SFML/Network.hpp>
#include "TcpClient.hpp"
#include <unordered_map>
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
        // static const std::unordered_map<std::string, void(*)(const TcpClient*)> functions;
        std::vector<PolishObject*> objects;
};

// const std::unordered_map<std::string, void(*)(const TcpClient*)> PolishClient::functions = {
//     {{1,2,3}, PolishClient::testFn}
// };