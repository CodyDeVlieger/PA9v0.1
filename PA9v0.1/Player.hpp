#include "Entity.hpp"

// Player class
class Player : public Entity<Player> {
public:
    Player(float x, float y, float radius, float speed)
        : Entity(x, y, radius, speed) {
        setColor(sf::Color::Green);
    }

    void update(const sf::Vector2f& target = sf::Vector2f(0, 0)) override {
        // Player movement via WASD
        sf::Vector2f direction(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1.f;

        // Normalize direction
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (magnitude != 0.f) {
            direction.x /= magnitude;
            direction.y /= magnitude;
        }

        updatePosition(direction.x, direction.y);
    }
};
