#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../PolishClient.hpp"
Suspendable Window::Process(PolishClient* polish)
{
    NOSUSPEND(); 
}

PolishObjectTypes Window::GetType()
{
    return T_Window;
}
Suspendable Window::Run()
{
    window->setActive(true);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(shape);
        window->display();
        SUSPEND();
    }
}
Window::Window(PolishClient* polish, unsigned width, unsigned height, unsigned x, unsigned y)
{
    window = new sf::RenderWindow(sf::VideoMode(width, height), "SFML works!");
    window->setPosition(sf::Vector2i(x,y));
    window->setActive(false);
    polish->AddCallback(this->Run());
}

Window::~Window()
{
    delete window;
    delete thread;
}