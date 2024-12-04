#include "Game.hpp"
#include <SFML/Graphics.hpp>

Game::Game()
    : window(sf::VideoMode(800, 600), "Top-Down Shooter"), player(400.0f, 300.0f),
    score(0), spawnTimer(0.0f), spawnInterval(2.0f), gameOver(false) {}

void Game::spawnEnemy() {
    float x = static_cast<float>(std::rand() % 800);
    float y = static_cast<float>(std::rand() % 600);
    enemies.emplace_back(x, y);
}

void Game::handleCollisions() {
    for (const auto& enemy : enemies) {
        if (player.getBounds().intersects(enemy.getBounds())) {
            gameOver = true;
        }
    }
}

void Game::showGameOverScreen() {
    window.clear();

    sf::Font font;
    font.loadFromFile("arial.ttf"); // Ensure you have a font file

    sf::Text gameOverText("Game Over", font, 50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(250, 200);

    sf::Text scoreText("Final Score: " + std::to_string(score), font, 30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(300, 300);

    window.draw(gameOverText);
    window.draw(scoreText);
    window.display();

    sf::sleep(sf::seconds(3));
    window.close();
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (gameOver) {
            showGameOverScreen();
            return;
        }

        // Update
        player.update(deltaTime);
        for (auto& enemy : enemies)
            enemy.update(deltaTime);

        spawnTimer += deltaTime;
        if (spawnTimer >= spawnInterval) {
            spawnEnemy();
            spawnTimer = 0.0f;
        }

        handleCollisions();

        // Render
        window.clear();
        player.draw(window);
        for (auto& enemy : enemies)
            enemy.draw(window);
        window.display();
    }
}