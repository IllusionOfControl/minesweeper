#ifndef MINESWEEPER_ABOUTSTATE_HPP
#define MINESWEEPER_ABOUTSTATE_HPP

#include "State.hpp"
#include "gui/Container.hpp"
#include "gui/Background.hpp"

class AboutState : public State {
public:
    explicit AboutState(GameContext& context);
    ~AboutState() override = default;

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;

private:
    Background mBackground;
    Container mGuiContainer;
};

#endif // MINESWEEPER_ABOUTSTATE_HPP