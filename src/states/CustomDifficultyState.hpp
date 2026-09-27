#ifndef MINESWEEPER_CUSTOMDIFFICULTYSTATE_HPP
#define MINESWEEPER_CUSTOMDIFFICULTYSTATE_HPP

#include "State.hpp"
#include "gui/Background.hpp"
#include "gui/Container.hpp"
#include "gui/Input.hpp"

class CustomDifficultyState : public State {
public:
    explicit CustomDifficultyState(GameContext& context);

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;

private:
    Background mBackground;
    Container mGuiContainer;

    Input::Ptr mWidthInput;
    Input::Ptr mHeightInput;
    Input::Ptr mMinesInput;

    bool mIsFormValid = false;
};

#endif // MINESWEEPER_CUSTOMDIFFICULTYSTATE_HPP
