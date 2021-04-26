#ifndef MINESWEEPER_RECORDSAVESTATE_H
#define MINESWEEPER_RECORDSAVESTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "MainMenuState.h"
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"

class RecordSaveState: public State {
public:
    RecordSaveState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();

private:
    GameDataRef _data;

    sf::Sprite _background;

    sf::Sprite _mainMenuButton;
    sf::Sprite _exitButton;
};


#endif //MINESWEEPER_RECORDSAVESTATE_H
