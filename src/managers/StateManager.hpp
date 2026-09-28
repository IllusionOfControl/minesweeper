#ifndef MINESWEEPER_STATEMANAGER_HPP
#define MINESWEEPER_STATEMANAGER_HPP

#include <functional>
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

#include "states/State.hpp"
#include "states/StateIdentifiers.hpp"

struct GameContext;

class StateManager {
public:
    enum class Action {
        Push,
        Pop,
        Change,
        Clear
    };

    StateManager() = default;
    explicit StateManager(GameContext& context);
    void setContext(GameContext& context) { mContext = &context; }
    ~StateManager() = default;

    StateManager(const StateManager&) = delete;
    StateManager& operator=(const StateManager&) = delete;

    template<typename T>
    void registerState(StateID stateId) {
        mFactories[stateId] = [this]() {
            return std::make_unique<T>(*mContext);
        };
    }
    void registerState(StateID stateId, std::function<StatePtr()> factory) {
        mFactories[stateId] = std::move(factory);
    }


    void pushState(StateID stateId);
    void changeState(StateID stateId);
    void popState();
    void clearStates();

    void processStateChanges();

    [[nodiscard]] State* getActiveState() const;

    [[nodiscard]] bool isEmpty() const { return mStateStack.empty(); }

private:
    struct PendingChange {
        Action action;
        StateID stateId = StateID::None;
    };

    StatePtr createState(StateID stateId);
    void applyChange(const PendingChange& change);

    GameContext* mContext = nullptr;
    std::stack<StatePtr> mStateStack;
    std::vector<PendingChange> mPendingChanges;
    std::unordered_map<StateID, std::function<StatePtr()>> mFactories;
};


#endif //MINESWEEPER_STATEMANAGER_HPP
