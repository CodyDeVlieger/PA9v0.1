#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Enemy.hpp"
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    Player player;
    std::vector<Enemy> enemies;
    int score;
    float spawnTimer;
    float spawnInterval;
    bool gameOver;

    void spawnEnemy();
    void handleCollisions();
    void showGameOverScreen();

public:
    Game();
    void run();
};

#endif // GAME_HPP