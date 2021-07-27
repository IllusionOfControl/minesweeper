#ifndef MINESWEEPER_DIFFICULTYMENUSTATE_H
#define MINESWEEPER_DIFFICULTYMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"
#include "State.h"
#include "GameState.h"
#include "AboutState.h"
#include "CustomDifficultyState.h"


class DifficultyMenuState: public State  {
public:
    DifficultyMenuState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();

private:
    GameDataRef _data;

    sf::Sprite _background;

    sf::Sprite _easyButton;
    sf::Sprite _mediumButton;
    sf::Sprite _hardButton;
    sf::Sprite _customButton;

    sf::Sprite _mainMenuButton;
    sf::Sprite _exitButton;
};


#endif
