#include "WindowFactory.hpp"
#include "Window.hpp"
#include<iostream>
#include "../PolishClient.hpp"
void WindowFactory::Process(PolishClient* polish)
{
    std::cout << "Instantiating a window" << std::endl;
    uint32_t width = polish->tcp->Read<uint32_t>();
    uint32_t height = polish->tcp->Read<uint32_t>();
    uint32_t x = polish->tcp->Read<uint32_t>();
    uint32_t y = polish->tcp->Read<uint32_t>();
    windows.push_back(new Window(polish, width, height, x, y));
}
PolishObject* WindowFactory::create(PolishClient* polish)
{
    std::cout << "Making a WindowFactory" << std::endl;
    return new WindowFactory(polish);
}
WindowFactory::~WindowFactory()
{

}
WindowFactory::WindowFactory(PolishClient* polish):polish(polish)
{

}

PolishObjectTypes WindowFactory::GetType()
{
    return T_WindowFactory;
}