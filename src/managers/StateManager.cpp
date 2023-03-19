#include "StateManager.hpp"

void StateManager::addState(StateRef newState, bool isReplacing)
{
    this->_isAdding = true;
    this->_isReplacing = isReplacing;

    this->mNewState = std::move(newState);
}

void StateManager::removeState()
{
    this->_isRemoving = true;
}

void StateManager::processStateChanges()
{
    if (this->_isRemoving && !this->mStateStack.empty())
    {
        this->mStateStack.pop();

        if (!this->mStateStack.empty())
        {
            //this->mStateStack.top()->Resume();
        }

        this->_isRemoving = false;
    }

    if (this->_isAdding)
    {
        if (!this->mStateStack.empty())
        {
            if (this->_isReplacing)
            {
                this->mStateStack.pop();
            }
            else
            {
                //this->mStateStack.top()->Pause();
            }
        }

        this->mStateStack.push(std::move(this->mNewState));
        this->mStateStack.top()->init();
        this->_isAdding = false;
    }
}

StateRef &StateManager::getActiveState()
{
    return this->mStateStack.top();
}