#ifndef MINESWEEPER_STATE_HPP
#define MINESWEEPER_STATE_HPP

#include <memory>


class State {
public:
    typedef std::unique_ptr<State> Ptr;
public:
    virtual void init() = 0;

    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};

typedef std::unique_ptr<State> StateRef;

#endif //MINESWEEPER_STATE_HPP
