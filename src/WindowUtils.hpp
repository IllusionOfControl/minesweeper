#ifndef MINESWEEPER_WINDOWUTILS_HPP
#define MINESWEEPER_WINDOWUTILS_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

inline void resizeWindow(sf::RenderWindow& window, const sf::Vector2u size) {
    window.setSize(size);
    window.setView(sf::View(sf::FloatRect({0.f, 0.f}, static_cast<sf::Vector2f>(size))));
}

#endif //MINESWEEPER_WINDOWUTILS_HPP
