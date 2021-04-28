#include <SFML/Graphics.hpp>


class Ellipse : public sf::Drawable {
private:
    float radius;
    float a;
    float b;
    float h = 0;    // x position, higher is further to the right
    float k = 0;    // y position, higher is further up
    sf::Color color = sf::Color::White;
    int detail = 100;
    sf::VertexArray vertices;

    void redraw();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


public:
    Ellipse(float _radius, float _a, float _b);
    void setColor(sf::Color _color);
    void setDetail(int _detail);
    void setPos(sf::Vector2f pos);
    void setPos(float x, float y);
    void move(sf::Vector2f dist);
    void move(float x, float y);
    bool inside(sf::Vector2f pos);
    bool inside(float x, float y);
    sf::Vector2f closestPoint(sf::Vector2f pos);
    sf::Vector2f normal(sf::Vector2f pos);
    
};