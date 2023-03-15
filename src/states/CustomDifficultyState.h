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
    explicit CustomDifficultyState(GameDataRef data);

    void Init() override;

    void HandleInput() override;
    void Update() override;
    void Draw() override;

private:
    GameDataRef mGameData;

    Container mContainer;

    sf::Sprite mBackground;

    Input::Ptr mWidthInput;
    Input::Ptr mHeightInput;
    Input::Ptr mMinesInput;

    bool mIsFormValid;
};


#endif //MINESWEEPER_CUSTOMDIFFICULTYSTATE_H
