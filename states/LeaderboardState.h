#ifndef MINESWEEPER_LEADERBOARDSTATE_H
#define MINESWEEPER_LEADERBOARDSTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "MainMenuState.h"
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"

class LeaderboardState: public State {
public:
    LeaderboardState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();

private:
    GameDataRef _data;

    sf::Sprite _background;
    sf::Sprite _textBgEasy;

    sf::Text _textEasyName;
    sf::Text _textEasyTime;

    sf::Sprite _mainMenuButton;
    sf::Sprite _exitButton;
};


#endif //MINESWEEPER_LEADERBOARDSTATE_H
