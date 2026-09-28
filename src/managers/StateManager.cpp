#include "StateManager.hpp"
#include <stdexcept>
#include <spdlog/spdlog.h>

StateManager::StateManager(GameContext& context)
    : mContext(&context) {
}

void StateManager::pushState(const StateID stateId) {
    spdlog::debug("Requested PushState: {}", toString(stateId));
    mPendingChanges.push_back({Action::Push, stateId});
}

void StateManager::changeState(const StateID stateId) {
    spdlog::debug("Requested ChangeState: {}", toString(stateId));
    mPendingChanges.push_back({Action::Change, stateId});
}

void StateManager::popState() {
    spdlog::debug("Requested PopState");
    mPendingChanges.push_back({Action::Pop, StateID::None});
}

void StateManager::clearStates() {
    spdlog::debug("Requested ClearStates");
    mPendingChanges.push_back({Action::Clear, StateID::None});
}

void StateManager::processStateChanges() {
    if (mPendingChanges.empty())
        return;

    for (const auto& change : mPendingChanges) {
        applyChange(change);
    }
    mPendingChanges.clear();
}

StatePtr StateManager::createState(StateID stateId) {
    auto it = mFactories.find(stateId);
    if (it == mFactories.end()) {
        spdlog::error("StateManager: Factory not found for StateID: {}", toString(stateId));
        throw std::runtime_error("StateManager: StateID not registered!");
    }
    return it->second();
}

void StateManager::applyChange(const PendingChange& change) {
    switch (change.action) {
        case Action::Push: {
            if (!mStateStack.empty()) {
                mStateStack.top()->pause();
            }
            auto newState = createState(change.stateId);
            spdlog::debug("Stack PUSH: {}", toString(change.stateId));
            mStateStack.push(std::move(newState));
            mStateStack.top()->init();
            break;
        }

        case Action::Change: {
            if (!mStateStack.empty()) {
                mStateStack.pop();
            }
            auto newState = createState(change.stateId);
            spdlog::debug("Stack CHANGE -> {}", toString(change.stateId));
            mStateStack.push(std::move(newState));
            mStateStack.top()->init();
            break;
        }

        case Action::Pop: {
            if (!mStateStack.empty()) {
                spdlog::debug("Stack POP");
                mStateStack.pop();
                if (!mStateStack.empty()) {
                    mStateStack.top()->resume();
                }
            }
            break;
        }

        case Action::Clear: {
            spdlog::debug("Stack CLEAR");
            while (!mStateStack.empty()) {
                mStateStack.pop();
            }
            break;
        }
    }
}

State* StateManager::getActiveState() const {
    if (mStateStack.empty())
        return nullptr;
    return mStateStack.top().get();
}