#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>

class MainMenu {
private:
    sf::RenderWindow& window;
    sf::RectangleShape startButton;

public:
    MainMenu(sf::RenderWindow& win);
    bool run();
};

#endif // MAINMENU_HPP