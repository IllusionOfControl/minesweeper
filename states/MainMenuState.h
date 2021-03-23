#ifndef MINESWEEPER_MAINMENUSTATE_H
#define MINESWEEPER_MAINMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"
#include "State.h"


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
//    sf::Sprite _optionButton;
//    sf::Sprite _exitButton;

    sf::Text _optionButton;
    sf::Text _exitButton;

    sf::Sprite _logo;
};


#endif //MINESWEEPER_MAINMENUSTATE_H
