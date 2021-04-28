#include <SFML/Graphics.hpp>
#include "ellipse.h"

/******************************/
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
/******************************/

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Billard");
    window.setFramerateLimit(144);  //pls don't burn my cpu

    Ellipse e(150, 1.1, 0.9);
    e.move(500.f, 500.f);

    /******************************/

    srand (time(NULL));

    int numcircs = 1600;

    sf::CircleShape circs[numcircs];
    for (int i = 0; i < numcircs; i++) {
        float rad = 4;
        circs[i].setRadius(rad);
        circs[i].setOrigin(rad,rad);
        sf::Vector2f p;
        p.x = rand() % 1280;
        p.y = rand() % 720;
        circs[i].setPosition(p);
        if (e.inside(p)) {
            circs[i].setFillColor(sf::Color::Green);
        } else {
            circs[i].setFillColor(sf::Color::Red);
        }
    }

    /******************************/

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
        for (int i = 0; i < numcircs; i++) window.draw(circs[i]);
        window.display();
    }

    return 0;
}
