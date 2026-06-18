#ifndef MINESWEEPER_STATEMANAGER_HPP
#define MINESWEEPER_STATEMANAGER_HPP

#include <memory>
#include <stack>

#include "../states/State.hpp"

// Explicit stack of screens. addState() replaces the top by default
// (isReplacing = true) or pushes on top of it (isReplacing = false);
// removeState() pops. States are cheap and rebuilt on navigation, so there is
// no Pause/Resume - going "back" simply pushes/replaces with a fresh state.
// Changes are deferred and applied by processStateChanges() once per frame.
class StateManager {
public:
    StateManager() { }
    ~StateManager() { }

    void addState(StateRef newState, bool isReplacing = true);
    void removeState();
    // run at the start of each frame
    void processStateChanges();

    StateRef &getActiveState();

    bool isEmpty() const { return mStateStack.empty(); }

private:
    std::stack<StateRef> mStateStack;
    State::Ptr mNewState;

    bool _isRemoving = false;
    bool _isAdding = false, _isReplacing = false;
};


#endif //MINESWEEPER_STATEMANAGER_HPP
