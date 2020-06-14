#include<iostream>
#include "RootConstructor.hpp"
#include "../TcpClient.hpp"
#include "../PolishClient.hpp"
void hexprint(const char* c, int len)
{
    for(int i=0;i<len;i++)
    {
        printf("%02x", (unsigned int)(unsigned char)(c[i]));
    }
}
void RootConstructor::Process(PolishClient* client)
{
    char id[32];
    client->tcp->Read(id, 32);
    try {
        client->objects.push_back(constructors.at(std::string(id, 32))(client));
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
RootConstructor::RootConstructor()
{

}
PolishObject* RootConstructor::testFn()
{
    std::cout << "Running testFn" << std::endl;
    return (PolishObject*)0;
}
PolishObjectTypes RootConstructor::GetType()
{
    return T_RootConstructor;
}