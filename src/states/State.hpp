#ifndef MINESWEEPER_STATE_HPP
#define MINESWEEPER_STATE_HPP

#include <memory>


struct GameContext;

class State {
public:
    using Ptr = std::unique_ptr<State>;

    explicit State(GameContext& context) : mContext(context) {}
    virtual ~State() = default;

    State(const State&) = delete;
    State& operator=(const State&) = delete;

    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void pause() {}
    virtual void resume() {}

protected:
    [[nodiscard]] GameContext& getContext() const noexcept { return mContext; }

private:
    GameContext& mContext;
};

using StatePtr = State::Ptr;

#endif //MINESWEEPER_STATE_HPP
