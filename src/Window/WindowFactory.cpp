#include "WindowFactory.hpp"
#include "Window.hpp"
#include<iostream>
#include "../PolishClient.hpp"
Suspendable WindowFactory::Process()
{
    // std::cout << "Instantiating a window" << std::endl;
    uint32_t width, height;
    WAIT_FOR(polish->socket->Read<uint32_t>(&width));
    WAIT_FOR(polish->socket->Read<uint32_t>(&height));
    // std::cout << "Making a window with width " << width << ", height " << height << std::endl;
    Window* window = new Window(polish, width, height, polish->objects.size());
    windows.push_back(window);
    polish->objects.push_back(window);
}
PolishObject* WindowFactory::create(PolishClient* polish, uint64_t id)
{
    // std::cout << "Making a WindowFactory" << std::endl;
    return new WindowFactory(polish, id);
}
WindowFactory::~WindowFactory()
{

}
WindowFactory::WindowFactory(PolishClient* polish, uint64_t id):PolishObject(polish, id)
{

}

PolishObjectTypes WindowFactory::GetType()
{
    return T_WindowFactory;
}