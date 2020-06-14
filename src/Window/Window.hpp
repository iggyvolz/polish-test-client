#pragma once
#include "../PolishObject.hpp"
#include "WindowFactory.hpp"
#include<thread>
#include<SFML/Graphics.hpp>
class Window: public PolishObject
{
    public:
        virtual void Process(PolishClient* polish);
        virtual PolishObjectTypes GetType();
        ~Window();
        void Run();
    private:
        Window(PolishClient* polish, unsigned width, unsigned height, unsigned x, unsigned y);
        friend void WindowFactory::Process(PolishClient* polish);
        PolishClient* polish;
        std::thread thread;
        sf::RenderWindow* window;
};