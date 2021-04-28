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

void Ellipse::setColor(sf::Color _color) {
    color = _color;
    redraw();
}

void Ellipse::setDetail(int _detail) {
    detail = _detail;
    redraw();
}

void Ellipse::setPos(sf::Vector2f pos) {
    setPos(pos.x, pos.y);
}

void Ellipse::setPos(float x, float y) {
    h = x;
    k = y;
    redraw();
}

bool Ellipse::inside(sf::Vector2f pos) {
    return inside(pos.x, pos.y);
}

bool Ellipse::inside(float x, float y) {
    return\
    (x - h) * (x - h) / (a*a*radius*radius) +\
    (y - k) * (y - k) / (b*b*radius*radius)\
    <= 1;
}