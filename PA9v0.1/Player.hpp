#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity {
private:
    float speed;

public:
    Player(float x, float y);
    void update(float deltaTime) override;
};

#endif // PLAYER_HPP