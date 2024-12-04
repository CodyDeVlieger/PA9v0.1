#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y) : Entity(x, y, { 30.0f, 30.0f }), speed(100.0f) {
    shape.setFillColor(sf::Color::Red);
}

void Enemy::update(float deltaTime) {
 
   
}