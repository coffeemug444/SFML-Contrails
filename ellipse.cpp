#include "ellipse.h"
#include "math.h"
#include <iostream>

Ellipse::Ellipse(float _radius, float _a, float _b) {
    radius = _radius;
    a = _a;
    b = _b;

    redraw();
}


void Ellipse::redraw() {
    vertices = sf::VertexArray(sf::LinesStrip, detail + 1);
    for(int i = 0; i < detail + 1; i++) {
        sf::Vector2f p;
        p.x = radius*a*cos(i * 2 * M_PI / detail) + h;
        p.y = radius*b*sin(i * 2 * M_PI / detail) + k;
        vertices[i].position = p;
        vertices[i].color = color;
    }
}

void Ellipse::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(vertices);
}

void Ellipse::move(sf::Vector2f dist) {
    move(dist.x, dist.y);
}

void Ellipse::move(float x, float y) {
    h += x;
    k += y;
    redraw();
}