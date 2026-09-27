#ifndef MINESWEEPER_DIFFICULTYMENUSTATE_HPP
#define MINESWEEPER_DIFFICULTYMENUSTATE_HPP

#include "State.hpp"
#include "gui/Background.hpp"
#include "gui/Container.hpp"


class DifficultyMenuState: public State  {
public:
    explicit DifficultyMenuState(GameContext& context);

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;

private:
    Background mBackground;
    Container mGuiContainer;
};

#endif
