#include "ellipse.h"
#include "math.h"

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
        p.x = a*cos(i * M_PI / detail) + h;
        p.y = b*sin(i * M_PI / detail) + k;
        vertices[i].position = p;
        vertices[i].color = color;
    }
}

void Ellipse::draw(sf::RenderTarget& target, sf::RenderStates states) {
    target.draw(vertices);
}