#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include <random>




// Template base class for characters
template <typename T>
class Entity {
public:
    sf::Vector2f position;
    sf::CircleShape shape;
    float speed;

    Entity(float x, float y, float radius, float speed)
        : position(x, y), speed(speed) {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(position);
    }

    void setColor(const sf::Color& color) {
        shape.setFillColor(color);
    }

    void updatePosition(float dx, float dy) {
        position.x += dx * speed;
        position.y += dy * speed;
        shape.setPosition(position);
    }

    virtual void update(const sf::Vector2f& target = sf::Vector2f(0, 0)) = 0;
};


