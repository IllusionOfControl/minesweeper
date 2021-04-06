#ifndef MINESWEEPER_ABOUTSTATE_H
#define MINESWEEPER_ABOUTSTATE_H

#include <SFML/Graphics.hpp>
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"
#include "MainMenuState.h"
#include "State.h"


class AboutState: public State {
public:
    AboutState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();

private:
    GameDataRef _data;

    sf::Sprite _background;

    sf::Sprite _mainMenuButton;
    sf::Sprite _exitButton;
    sf::Sprite _logo;

    sf::Sprite _authorButton;
};


#endif //MINESWEEPER_ABOUTSTATE_H
