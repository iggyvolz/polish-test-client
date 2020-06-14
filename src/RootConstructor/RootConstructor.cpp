#include<iostream>
#include "RootConstructor.hpp"
#include "TcpClient.hpp"
#include "PolishClient.hpp"
void RootConstructor::Process(PolishClient* client)
{
    char id[32];
    client->tcp->Read(id, 32);
    try {
        client->objects.push_back(constructors.at(std::string(id, 32))());
    } catch(const std::out_of_range& err)
    {
        std::cout << "Attempted to initialize object with unknown ID '";
        for(int i=0;i<32;i++)
        {
            std::cout << (int)(id[i]) << "/";
        }
        std::cout << "'" << std::endl;
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


const std::unordered_map<std::string, PolishObject*(*)()> RootConstructor::constructors = {
	{std::string({19,106,-100,-29,107,-22,64,106,113,-100,-93,74,-107,-16,11,110,103,50,109,127,1,-13,45,41,7,36,34,-4,117,-16,88,-101}, 32), RootConstructor::testFn}
};
