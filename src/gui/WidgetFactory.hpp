#ifndef MINESWEEPER_WIDGETFACTORY_HPP
#define MINESWEEPER_WIDGETFACTORY_HPP

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include "Button.hpp"
#include "../MineSweeper.hpp"

// Builders for the widgets that every screen shares (the top-left "back to main
// menu" button, the top-right exit button and the tiled background), so each
// state no longer repeats the same setup code.
namespace widgets {
    // Configure a background sprite to fill the current window.
    void setupBackground(sf::Sprite &sprite, const GameDataRef &context);

    // Top-left button that returns to the main menu.
    std::shared_ptr<Button> makeMainMenuButton(const GameDataRef &context);

    // Top-right button that closes the window. widthInSquares is the playfield
    // width used to place the button at the right edge.
    std::shared_ptr<Button> makeExitButton(const GameDataRef &context, int widthInSquares);
}

#endif //MINESWEEPER_WIDGETFACTORY_HPP
