#ifndef MINESWEEPER_WINDOWUTILS_HPP
#define MINESWEEPER_WINDOWUTILS_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

// Resize the (already created) window and keep a 1:1 pixel view, instead of
// destroying and recreating the OS window on every screen change (B4).
inline void resizeWindow(sf::RenderWindow &window, unsigned int width, unsigned int height) {
    window.setSize({width, height});
    window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))));
}

#endif //MINESWEEPER_WINDOWUTILS_HPP
