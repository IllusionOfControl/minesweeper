#ifndef MINESWEEPER_RECORDSAVESTATE_H
#define MINESWEEPER_RECORDSAVESTATE_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include "State.h"
#include "MainMenuState.h"
#include "LeaderboardState.h"
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

    sf::Sprite _nameTextBg;
    sf::Sprite _nameLogo;
    sf::Text _nameInputText;

    sf::Sprite _timeTextBg;
    sf::Sprite _timeLogo;
    sf::Text _timeText;

    sf::String _nameStr;
    sf::String _timeStr;

    sf::Sprite _saveButton;
    sf::Sprite _exitButton;
    sf::Sprite _mainMenuButton;
};


#endif //MINESWEEPER_RECORDSAVESTATE_H
