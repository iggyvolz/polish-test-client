#include<iostream>
#include "Root.hpp"
#include "../Socket.hpp"
#include "../PolishClient.hpp"
#include "../DummyObject.hpp"
void hexprint(const char* c, int len)
{
    for(int i=0;i<len;i++)
    {
        printf("%02x", (unsigned int)(unsigned char)(c[i]));
    }
}
void hexprint(std::string s)
{
    hexprint(s.c_str(), s.length());
}
Suspendable Root::Process()
{
    char id[32];
    WAIT_FOR(polish->socket->Read(id, 32));
    std::string identifier(id, 32);
    bool dummy = constructors.find(identifier) == constructors.end();
    if(dummy) {
        printf("Creating dummy object, did not find type ");
        hexprint(identifier);
        printf("\n");
        polish->objects.push_back(DummyObject::create(polish, polish->objects.size()));
    } else {
        printf("Creating object of type ");
        hexprint(identifier);
        printf("\n");
        polish->objects.push_back(constructors.at(identifier)(polish, polish->objects.size()));
    }
    // Validate Contract Object
    WAIT_FOR(polish->socket->Write(this->id));
    WAIT_FOR(polish->socket->Write(id));
    WAIT_FOR(polish->socket->Write<char>(dummy?0:1));
}
Root::Root(PolishClient* polish, uint64_t id):PolishObject(polish,id)
{

}
PolishObjectTypes Root::GetType()
{
    return T_Root;
}