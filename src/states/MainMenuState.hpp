#ifndef MINESWEEPER_MAINMENUSTATE_HPP
#define MINESWEEPER_MAINMENUSTATE_HPP

#include "State.hpp"
#include "gui/Background.hpp"
#include "gui/Container.hpp"
#include "gui/Image.hpp"


class MainMenuState : public State {
public:
    explicit MainMenuState(GameContext& context)
        : State(context) {}

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;

private:
    Background mBackground;
    Image mLogo;
    Container mGuiContainer;
};


#endif //MINESWEEPER_MAINMENUSTATE_HPP
