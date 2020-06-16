#pragma once
#include "../PolishObject.hpp"
#include "WindowFactory.hpp"
#include<thread>
#include<SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Window: public PolishObject
{
    public:
        virtual Suspendable Process(PolishClient* polish);
        virtual PolishObjectTypes GetType();
        ~Window();
        void Run();
    private:
        Window(PolishClient* polish, unsigned width, unsigned height, unsigned x, unsigned y);
        friend Suspendable WindowFactory::Process(PolishClient* polish);
        PolishClient* polish;
        sf::Thread* thread;
        sf::RenderWindow* window;
};