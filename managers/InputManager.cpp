//
// Created by Illusion of control on 20.03.2021.
//

#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::RenderWindow &window)
{
    sf::IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

    if (playButtonRect.contains(sf::Mouse::getPosition(window)))
    {
        return true;
    }

    return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window)
{
    return sf::Mouse::getPosition(window);
}