#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include <random>
#include "Player.hpp"
#include "Enemy.hpp"




int main() {
    // Window setup
    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Top-Down Shooter");
    window.setFramerateLimit(60);

    // Create player
    Player player(windowWidth / 2.f, windowHeight / 2.f, 15.f, 5.f);

    // Enemy list
    std::vector<std::unique_ptr<Enemy>> enemies;

    // Game loop
    sf::Clock spawnClock;
    sf::Clock gameClock;
    float spawnRate = 2.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Spawn enemies
        if (spawnClock.getElapsedTime().asSeconds() > spawnRate) {
            auto pos = getRandomPosition(windowWidth, windowHeight);
            enemies.push_back(std::make_unique<Enemy>(pos.x, pos.y, 10.f, 2.f));
            spawnClock.restart();
            spawnRate = std::max(0.5f, spawnRate - 0.1f); // Gradually decrease spawn rate
        }

        // Update player
        player.update();

        // Update enemies
        for (auto& enemy : enemies) {
            enemy->update(player.position);
        }

        // Render
        window.clear();
        window.draw(player.shape);
        for (const auto& enemy : enemies) {
            window.draw(enemy->shape);
        }
        window.display();
    }

    return 0;
}