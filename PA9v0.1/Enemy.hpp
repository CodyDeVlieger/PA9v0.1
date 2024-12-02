#include "Entity.hpp"



// Enemy class
class Enemy : public Entity<Enemy> {
public:
    Enemy(float x, float y, float radius, float speed)
        : Entity(x, y, radius, speed) {
        setColor(sf::Color::Red);
    }

    void update(const sf::Vector2f& target) override {
        // Move towards the target
        sf::Vector2f direction = target - position;
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (magnitude != 0.f) {
            direction.x /= magnitude;
            direction.y /= magnitude;
        }
        updatePosition(direction.x, direction.y);
    }
};

// Helper function to spawn enemies at random locations
sf::Vector2f getRandomPosition(int windowWidth, int windowHeight) {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> distX(0, windowWidth);
    static std::uniform_int_distribution<int> distY(0, windowHeight);
    return sf::Vector2f(distX(rng), distY(rng));
}
