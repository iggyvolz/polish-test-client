#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../PolishClient.hpp"
Suspendable Window::Process()
{
    uint64_t method;
    WAIT_FOR(polish->socket->Read(&method));
    if(method == 0) {
        WAIT_FOR(this->SetTitle());
    } else if(method == 1) {
        WAIT_FOR(this->SetPosition());
    } else {
            std::cout << "Unknown method #" << method << " on Window" << std::endl;
            std::exit(1);
    }
}

Suspendable Window::SetTitle()
{
    char titleLength;
    WAIT_FOR(polish->socket->Read(&titleLength));
    char* title = (char*)malloc(sizeof(char)*titleLength);
    WAIT_FOR(polish->socket->Read(title, titleLength));
    window->setTitle(title);
}

Suspendable Window::SetPosition()
{
    uint32_t x, y;
    WAIT_FOR(polish->socket->Read(&x));
    WAIT_FOR(polish->socket->Read(&y));
    window->setPosition(sf::Vector2i(x,y));

}

PolishObjectTypes Window::GetType()
{
    return T_Window;
}
Suspendable Window::Run()
{
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
Window::Window(PolishClient* polish, unsigned width, unsigned height, uint64_t id):PolishObject(polish,id)
{
    window = new sf::RenderWindow(sf::VideoMode(width, height), "SFML works!");
    polish->AddCallback(this->Run());
}

Window::~Window()
{
    delete window;
    delete thread;
}