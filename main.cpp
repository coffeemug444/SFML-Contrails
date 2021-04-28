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

    Ellipse e(150, 1.1, 0.9);
    e.move(640.f, 360.f);

    sf::Clock clock;
    sf::Int32 prevTime = clock.getElapsedTime().asMilliseconds();
    sf::Int32 currTime;
    sf::Int32 delt;

    sf::CircleShape circ;
    circ.setRadius(3);
    circ.setOrigin(sf::Vector2f(3,3));
    circ.setFillColor(sf::Color::Green);
    circ.setPosition(550, 360);
    sf::Vector2f vel(0,80);

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

        circ.move(vel.x * delt / 1000.f, vel.y * delt / 1000.f);

        if (!e.inside(circ.getPosition())) {
            vel = reflect(vel, e.normal(circ.getPosition()));
        }

        window.clear();
        window.draw(e);
        window.draw(circ);
        window.display();
    }

    return 0;
}
