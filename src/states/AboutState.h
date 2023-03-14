#ifndef MINESWEEPER_ABOUTSTATE_H
#define MINESWEEPER_ABOUTSTATE_H

#include <SFML/Graphics.hpp>
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"
#include "MainMenuState.h"
#include "State.h"
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


#endif //MINESWEEPER_ABOUTSTATE_H
