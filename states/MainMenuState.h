#ifndef MINESWEEPER_MAINMENUSTATE_H
#define MINESWEEPER_MAINMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"
#include "State.h"
#include "GameState.h"
#include "AboutState.h"
#include "DifficultyMenuState.h"
#include "LeaderboardState.h"


class MainMenuState: public State {
public:
    MainMenuState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();

private:
    GameDataRef _data;

    sf::Sprite _background;

    sf::Sprite _playButton;
    sf::Sprite _aboutButton;
    sf::Sprite _leaderboardsButton;
    sf::Sprite _exitButton;

    sf::Sprite _logo;
};


#endif //MINESWEEPER_MAINMENUSTATE_H
