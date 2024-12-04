#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include <random>
#include <sstream>
#include "Entity.hpp"

int main() {
    // Window setup
    const int windowWidth = 1000;
    const int windowHeight = 800;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Top-Down Shooter");
    window.setFramerateLimit(60);

    // Create player
    Player player(windowWidth / 2.f, windowHeight / 2.f, 15.f, 5.f);

    // Enemy list
    std::vector<std::unique_ptr<Enemy>> enemies;

    // Projectile list
    std::vector<std::unique_ptr<Projectile>> projectiles;

    // Last movement direction
    sf::Vector2f lastDirection(0, -1); // Default to upward shooting

    // Score tracking
    int score = 0;
    sf::Font font;
   // font.loadFromFile("arial.ttf"); // Ensure you have a font file
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);

    // Clocks for timing
    sf::Clock spawnClock;
    sf::Clock gameClock;
    float spawnRate = 2.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update player
        sf::Vector2f direction(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1.f;

        if (direction != sf::Vector2f(0.f, 0.f)) {
            // Determine the last cardinal direction
            if (std::abs(direction.x) > std::abs(direction.y)) {
                lastDirection = (direction.x > 0) ? sf::Vector2f(1.f, 0.f) : sf::Vector2f(-1.f, 0.f); // Left or Right
            }
            else {
                lastDirection = (direction.y > 0) ? sf::Vector2f(0.f, 1.f) : sf::Vector2f(0.f, -1.f); // Down or Up
            }
        }


        player.update();

        // Shoot projectile
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            // Normalize the last direction for shooting
            sf::Vector2f normalizedDirection = lastDirection;
            if (normalizedDirection.x != 0) normalizedDirection.x = (normalizedDirection.x > 0) ? 1.f : -1.f;
            if (normalizedDirection.y != 0) normalizedDirection.y = (normalizedDirection.y > 0) ? 1.f : -1.f;

            projectiles.push_back(std::make_unique<Projectile>(
                player.position.x, player.position.y, 5.f, 10.f, normalizedDirection
            ));
        }

        // Spawn enemies
        if (spawnClock.getElapsedTime().asSeconds() > spawnRate) {
            auto pos = getRandomPosition(windowWidth, windowHeight);
            enemies.push_back(std::make_unique<Enemy>(pos.x, pos.y, 10.f, 2.f));
            spawnClock.restart();
            spawnRate = std::max(0.5f, spawnRate - 0.1f); // Gradually decrease spawn rate
        }

        // Update projectiles
        for (auto& projectile : projectiles) {
            projectile->update();
        }

        // Update enemies
        for (auto& enemy : enemies) {
            enemy->update(player.position);
        }

        // Check collisions
        for (auto it = projectiles.begin(); it != projectiles.end();) {
            bool removed = false;
            for (auto jt = enemies.begin(); jt != enemies.end();) {
                if ((*it)->shape.getGlobalBounds().intersects((*jt)->shape.getGlobalBounds())) {
                    it = projectiles.erase(it);
                    jt = enemies.erase(jt);
                    score++;
                    removed = true;
                    break;
                }
                else {
                    ++jt;
                }
            }
            if (!removed) {
                ++it;
            }
        }

        // Remove projectiles out of bounds
        projectiles.erase(
            std::remove_if(projectiles.begin(), projectiles.end(),
                [windowWidth, windowHeight](const std::unique_ptr<Projectile>& projectile) {
                    return projectile->position.x < 0 || projectile->position.x > windowWidth ||
                        projectile->position.y < 0 || projectile->position.y > windowHeight;
                }),
            projectiles.end());

        // Render
        window.clear();

        // Update score text
        std::ostringstream scoreStream;
        scoreStream << "Score: " << score;
        scoreText.setString(scoreStream.str());
        window.draw(scoreText);

        window.draw(player.shape);
        for (const auto& enemy : enemies) {
            window.draw(enemy->shape);
        }
        for (const auto& projectile : projectiles) {
            window.draw(projectile->shape);
        }

        window.display();
    }

    return 0;
}