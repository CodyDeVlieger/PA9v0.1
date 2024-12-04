#include "Entity.hpp"

Entity::Entity(float x, float y, sf::Vector2f size) : position(x, y) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setOrigin(size.x / 2, size.y / 2); // Center the origin
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Entity::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Entity::getPosition() const {
    return position;
}