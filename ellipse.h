#include <SFML/Graphics.hpp>


class Ellipse : sf::Drawable {
private:
    float radius;
    float a;
    float b;
    float h;    // x position, higher is further to the right
    float k;    // y position, higher is further up
    int detail = 100;
    sf::VertexArray vertices;

public:
    Ellipse(float _radius, float _a, float _b);
    void setColor(sf::Color color);
    void setDetail(int new_detail);
    void setPos(sf::Vector2f pos);
    void move(sf::Vector2f dist);
    bool inside(sf::Vector2f pos);
    sf::Vector2f closestPoint(sf::Vector2f pos);
    sf::Vector2f normal(sf::Vector2f pos);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
};