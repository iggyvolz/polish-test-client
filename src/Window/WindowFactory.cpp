#include "WindowFactory.hpp"
#include "Window.hpp"
#include<iostream>
#include "../PolishClient.hpp"
Suspendable WindowFactory::Process(PolishClient* polish)
{
    std::cout << "Instantiating a window" << std::endl;
    uint32_t width, height, x, y;
    WAIT_FOR(polish->tcp->Read<uint32_t>(&width));
    WAIT_FOR(polish->tcp->Read<uint32_t>(&height));
    WAIT_FOR(polish->tcp->Read<uint32_t>(&x));
    WAIT_FOR(polish->tcp->Read<uint32_t>(&y));
    std::cout << "Making a window with width " << width << ", height " << height << ", x " << x << ", y " << y << std::endl;
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