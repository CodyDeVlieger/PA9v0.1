#pragma once

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
