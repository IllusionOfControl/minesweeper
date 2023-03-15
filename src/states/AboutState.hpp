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
    AboutState(GameDataRef data);

    void Init();

    void HandleInput();

    void Update();

    void Draw();

private:
    GameDataRef mGameData;

    sf::Sprite mBackground;
    sf::Sprite mLogo;
    Container mGuiContainer;
};


#endif //MINESWEEPER_ABOUTSTATE_HPP
