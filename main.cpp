#include <SFML/Graphics.hpp>
#include "ellipse.h"


// reflects a vector `d` in a normal `n`
sf::Vector2f reflect(sf::Vector2f d, sf::Vector2f n) {
    sf::Vector2f r;
    float scale = 2*(d.x*n.x + d.y*n.y);
    r.x = d.x - scale*n.x;
    r.y = d.y - scale*n.y;
    return r;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Billard");
    window.setFramerateLimit(144);  //pls don't burn my cpu

    Ellipse e(190, 1.1, 0.9);
    e.move(640.f, 360.f);

    sf::Clock clock;
    sf::Int32 prevTime = clock.getElapsedTime().asMilliseconds();
    sf::Int32 currTime;
    sf::Int32 delt;

    int num = 500;
    sf::CircleShape circs[num];
    for (int i = 0; i < num; i++) {
        circs[i].setRadius(1);
        circs[i].setFillColor(sf::Color::Green);
        circs[i].setPosition(550 + i / 20.f, 360);
    }

    sf::Vector2f vels[num];
    for (int i = 0; i < num; i++) {
        vels[i].x = 20;
        vels[i].y = 160;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        currTime = clock.getElapsedTime().asMilliseconds();
        delt = currTime - prevTime;
        prevTime = currTime;


        window.clear();

        for (int i = 0; i < num; i++) {
            circs[i].move(vels[i].x * delt / 1000.f, vels[i].y * delt / 1000.f);

            if (!e.inside(circs[i].getPosition())) {
                circs[i].move(-vels[i].x * delt / 1000.f, -vels[i].y * delt / 1000.f);
                vels[i] = reflect(vels[i], e.normal(circs[i].getPosition()));
            }

            window.draw(circs[i]);

        }


        window.draw(e);
        window.display();
    }

    return 0;
}
