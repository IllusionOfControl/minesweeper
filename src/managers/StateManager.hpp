#ifndef MINESWEEPER_STATEMANAGER_HPP
#define MINESWEEPER_STATEMANAGER_HPP

#include <memory>
#include <stack>

#include "../states/State.hpp"

class StateManager {
public:
    StateManager() { }
    ~StateManager() { }

    void addState(StateRef newState, bool isReplacing = true);
    void removeState();
    // run at start of each loop in Game.cpp
    void processStateChanges();

    StateRef &getActiveState();

private:
    std::stack<StateRef> mStateStack;
    State::Ptr mNewState;

    bool _isRemoving;
    bool _isAdding, _isReplacing;
};


#endif //MINESWEEPER_STATEMANAGER_HPP
