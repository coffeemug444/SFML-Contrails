#include <SFML/Graphics.hpp>
#include "ellipse.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Billard");
    window.setFramerateLimit(144);  //pls don't burn my cpu

    Ellipse e(150, 1.1, 0.9);
    e.move(640.f, 360.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(e);
        window.display();
    }

    return 0;
}
