#ifndef MINESWEEPER_CUSTOMDIFFICULTYSTATE_H
#define MINESWEEPER_CUSTOMDIFFICULTYSTATE_H

#include <SFML/Graphics.hpp>
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"
#include "State.h"
#include "GameState.h"
#include "AboutState.h"
#include "DifficultyMenuState.h"
#include "../gui/Container.hpp"
#include "../gui/Input.hpp"


class CustomDifficultyState : public State {
public:
    CustomDifficultyState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();

private:
    GameDataRef mGameData;

    Container mContainer;

    sf::Sprite _background;

    Input::Ptr mWidthInput;
    Input::Ptr mHeightInput;
    Input::Ptr mMinesInput;

    bool isFormValid;
};


#endif //MINESWEEPER_CUSTOMDIFFICULTYSTATE_H
