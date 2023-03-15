#ifndef MINESWEEPER_CUSTOMDIFFICULTYSTATE_HPP
#define MINESWEEPER_CUSTOMDIFFICULTYSTATE_HPP

#include <SFML/Graphics.hpp>
#include "../MineSweeper.hpp"
#include "../DEFINITIONS.h"
#include "State.hpp"
#include "GameState.hpp"
#include "AboutState.hpp"
#include "DifficultyMenuState.hpp"
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


#endif //MINESWEEPER_CUSTOMDIFFICULTYSTATE_HPP
