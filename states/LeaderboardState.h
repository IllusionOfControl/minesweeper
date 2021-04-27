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

    sf::Sprite _bannerEasy;
    sf::Sprite _textBgEasy;
    sf::Text _textEasyName;
    sf::Text _textEasyTime;

    sf::Sprite _bannerNormal;
    sf::Sprite _textBgNormal;
    sf::Text _textNormalName;
    sf::Text _textNormalTime;

    sf::Sprite _bannerHard;
    sf::Sprite _textBgHard;
    sf::Text _textHardName;
    sf::Text _textHardTime;

    sf::Sprite _mainMenuButton;
    sf::Sprite _exitButton;
};


#endif //MINESWEEPER_LEADERBOARDSTATE_H
