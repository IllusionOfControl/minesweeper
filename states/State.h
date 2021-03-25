#ifndef MINESWEEPER_STATE_H
#define MINESWEEPER_STATE_H

#include <memory>


class State {
public:
    virtual void Init() = 0;

    virtual void HandleInput() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

typedef std::unique_ptr<State> StateRef;

#endif //MINESWEEPER_STATE_H
