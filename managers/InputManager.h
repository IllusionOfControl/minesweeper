#ifndef MINESWEEPER_INPUTMANAGER_H
#define MINESWEEPER_INPUTMANAGER_H

#include "SFML/Graphics.hpp"

class InputManager {
public:
    InputManager() {}
    ~InputManager() {}

    bool IsSpriteClicked(sf::Sprite object, sf::RenderWindow &window);

    sf::Vector2i GetMousePosition(sf::RenderWindow &window);
};


#endif //MINESWEEPER_INPUTMANAGER_H
