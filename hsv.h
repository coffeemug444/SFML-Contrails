#include <SFML/Graphics.hpp>

sf::Color hsv(float in) {
    sf::Color col;
    col.a = 255;
    
    in *= 6;

    if (in < 1) {
        col.r = 255;
        col.g = 255 * in;
        col.b = 0;
        return col;
    }
    in -= 1;
    if (in < 1) {
        col.r = 255 * (1.f - in);
        col.g = 255;
        col.b = 0;
        return col;
    }
    in -= 1;
    if (in < 1) {
        col.r = 0;
        col.g = 255;
        col.b = 255 * in;
        return col;
    }
    in -= 1;
    if (in < 1) {
        col.r = 0;
        col.g = 255 * (1.f - in);
        col.b = 255;
        return col;
    }
    in -= 1;
    if (in < 1) {
        col.r = 255 * in;
        col.g = 0;
        col.b = 255;
        return col;
    }
    in -= 1;
    col.r = 255;
    col.g = 0;
    col.b = 255 * (1.f - in);
    return col;
}