#include <SFML/Graphics.hpp>
#include "ellipse.h"
#include "hsv.h"


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

    float a = 1.f;
    float b = 1.f;
    
    Ellipse e(190, a, b);
    e.move(640.f, 360.f);

    sf::Clock clock;
    sf::Int32 prevTime = clock.getElapsedTime().asMilliseconds();
    sf::Int32 currTime;
    sf::Int32 leftoverTime = 0;
    sf::Int32 delt;

    int num = 10000;
    sf::CircleShape circs[num];
    for (int i = 0; i < num; i++) {
        circs[i].setRadius(1);
        circs[i].setFillColor(hsv((float)i / num));
        circs[i].setPosition(550 + i / 80.f, 360);
    }

    sf::Vector2f vels[num];
    for (int i = 0; i < num; i++) {
        vels[i].x = 120;
        vels[i].y = 240;
        vels[i] *= 0.5f;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)) {
                a *= 1.1;
                e.setab(a,b);
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)) {
                a /= 1.1;
                e.setab(a,b);
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)) {
                b *= 1.1;
                e.setab(a,b);
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)) {
                b /= 1.1;
                e.setab(a,b);
            }
        }

        int timestep = 1;       // timestep in ms, eg. 5ms = 200hz phys calcs
        currTime = clock.getElapsedTime().asMilliseconds();
        delt = currTime - prevTime;
        prevTime = currTime;
        delt += leftoverTime;
        sf::Int32 timesteps = delt / timestep;
        leftoverTime = delt - timesteps * timestep;



        window.clear();
        for (int ts = 0; ts < timesteps; ts++) {
            for (int i = 0; i < num; i++) {
                circs[i].move(vels[i].x * timestep / 1000.f, vels[i].y * timestep / 1000.f);

                if (!e.inside(circs[i].getPosition())) {
                    circs[i].move(-vels[i].x * timestep / 1000.f, -vels[i].y * timestep / 1000.f);
                    vels[i] = reflect(vels[i], e.normal(circs[i].getPosition()));
                }
            }
        }

        for (int i = 0; i < num; i++)   window.draw(circs[i]);
        window.draw(e);
        window.display();
    }

    return 0;
}
