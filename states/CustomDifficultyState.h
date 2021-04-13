#ifndef MINESWEEPER_CUSTOMDIFFICULTYSTATE_H
#define MINESWEEPER_CUSTOMDIFFICULTYSTATE_H

#include <SFML/Graphics.hpp>
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"
#include "State.h"
#include "GameState.h"
#include "AboutState.h"
#include "DifficultyMenuState.h"


class CustomDifficultyState : public State {
public:
    CustomDifficultyState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();

private:
    GameDataRef _data;

    sf::Sprite _background;
    sf::Sprite _playButton;

    sf::Sprite _widthLogo;
    sf::Sprite _heightLogo;
    sf::Sprite _minesLogo;

    sf::Sprite _widthTextBackground;
    sf::Sprite _heightTextBackground;
    sf::Sprite _minesTextBackground;

    sf::Text _widthText;
    sf::Text _heightText;
    sf::Text _minesText;

    sf::String _widthString;
    sf::String _heightString;
    sf::String _minesString;

    sf::Sprite _mainMenuButton;
    sf::Sprite _exitButton;

    bool isValidDifficulty;
};


#endif //MINESWEEPER_CUSTOMDIFFICULTYSTATE_H
