#ifndef MINESWEEPER_EMPTYSTATE_HPP
#define MINESWEEPER_EMPTYSTATE_HPP

#include "State.hpp"


class EmptyState : public State {
public:
    explicit EmptyState(GameContext& context)
        : State(context) {}

    ~EmptyState() override = default;

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;
};


#endif //MINESWEEPER_EMPTYSTATE_HPP