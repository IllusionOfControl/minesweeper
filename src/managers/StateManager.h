#ifndef MINESWEEPER_STATEMANAGER_H
#define MINESWEEPER_STATEMANAGER_H

#include <memory>
#include <stack>

#include "../states/State.h"

class StateManager {
public:
    StateManager() { }
    ~StateManager() { }

    void AddState(StateRef newState, bool isReplacing = true);
    void RemoveState();
    // Run at start of each loop in Game.cpp
    void ProcessStateChanges();

    StateRef &GetActiveState();

private:
    std::stack<StateRef> _states;
    StateRef _newState;

    bool _isRemoving;
    bool _isAdding, _isReplacing;
};


#endif //MINESWEEPER_STATEMANAGER_H
