#include<iostream>
#include "RootConstructor.hpp"
#include "../Socket.hpp"
#include "../PolishClient.hpp"
void hexprint(const char* c, int len)
{
    for(int i=0;i<len;i++)
    {
        printf("%02x", (unsigned int)(unsigned char)(c[i]));
    }
}
Suspendable RootConstructor::Process()
{
    char id[32];
    WAIT_FOR(polish->socket->Read(id, 32));
    try {
        polish->objects.push_back(constructors.at(std::string(id, 32))(polish, polish->objects.size()));
    } catch(const std::out_of_range& err)
    {
        std::cout << "Attempted to initialize object with unknown ID '";
        hexprint(id, 32);
        std::cout << "'" << std::endl;
        std::cout << "Have the following IDs:" << std::endl;
        for(auto it = constructors.begin(); it != constructors.end(); it++)
        {
            std::cout << "    ";
            hexprint(it->first.c_str(), 32);
            std::cout << std::endl;
        }
    }
}
RootConstructor::RootConstructor(PolishClient* polish):polish(polish)
{

}
PolishObjectTypes RootConstructor::GetType()
{
    return T_RootConstructor;
}