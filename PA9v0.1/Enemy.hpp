#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity {
private:
    float speed;

public:
    Enemy(float x, float y);
    void update(float deltaTime) override;
};

#endif // ENEMY_HPP