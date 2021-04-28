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

sf::Vector2f Ellipse::normal(sf::Vector2f pos) {
    return normal(pos.x, pos.y);
}

sf::Vector2f Ellipse::normal(float x, float y) {
    // just assume x & y are points on the ellipse, w/e

    // special checks for when we're looking at y = h +- r*sqrt(a)
    // just to avoid divide by 0 errors

    if (y == h + radius*sqrt(a)) {
        // on the very right edge of the ellipse
        return sf::Vector2f(-1, 0);
    } else if (y == h - radius*sqrt(a)) {
        // on the very left edge of the ellipse
        return sf::Vector2f(1, 0);
    }

    
    float dy = (b*(h-x))/(a*(y-k));

    sf::Vector2f tangent(1, dy);

    // now turn tangent into normal
    // ensure the normal points inside the ellipse by
    // checking all four quadrants

    sf::Vector2f norm;

    norm.y = abs(tangent.x);
    norm.x = abs(tangent.y);

    if (x > h) {
        norm.x *= -1;
    }

    if (y > k) {
        norm.y *= -1;
    }

    float scale = 1.f/sqrt(norm.y*norm.y + norm.x*norm.x);
    norm.x *= scale;
    norm.y *= scale;

    return norm;

}

void Ellipse::setab(float _a, float _b) {
    a = _a;
    b = _b;
    redraw();
}