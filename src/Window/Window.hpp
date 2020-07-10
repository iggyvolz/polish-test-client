#pragma once
#include "../PolishObject.hpp"
#include "WindowFactory.hpp"
#include<thread>
#include<SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../PolishClient.hpp"
class Window: public PolishObject
{
    public:
        virtual Suspendable Process();
        virtual PolishObjectTypes GetType();
        ~Window();
        Suspendable Run();
    private:
        Window(PolishClient* polish, unsigned width, unsigned height, uint64_t id);
        friend Suspendable WindowFactory::Process();
        sf::Thread* thread;
        sf::RenderWindow* window;
        Suspendable SetTitle();
        Suspendable SetPosition();
};