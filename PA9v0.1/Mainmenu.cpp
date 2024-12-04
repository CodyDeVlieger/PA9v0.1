#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow& win) : window(win) {
    startButton.setSize({ 200.0f, 50.0f });
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300.0f, 275.0f);
}

bool MainMenu::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (startButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    return true;
            }
        }

        window.clear();
        window.draw(startButton);
        window.display();
    }
    return false;
}