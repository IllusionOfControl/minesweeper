#ifndef MINESWEEPER_ABOUTSTATE_HPP
#define MINESWEEPER_ABOUTSTATE_HPP

#include <SFML/Graphics.hpp>
#include "../MineSweeper.hpp"
#include "../DEFINITIONS.h"
#include "MainMenuState.hpp"
#include "State.hpp"
#include "../gui/Container.hpp"

class AboutState : public State {
public:
    AboutState(GameDataRef context);

    void init();

    void handleInput();

    void update();

    void draw();

private:
    GameDataRef mContext;

    sf::Sprite mBackground;
    sf::Sprite mLogo;
    Container mGuiContainer;
};


#endif //MINESWEEPER_ABOUTSTATE_HPP
