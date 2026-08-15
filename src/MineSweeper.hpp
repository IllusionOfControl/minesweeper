#ifndef MINESWEEPER_MINESWEEPER_HPP
#define MINESWEEPER_MINESWEEPER_HPP

#include "managers/AssetManager.hpp"
#include "managers/StateManager.hpp"
#include "Difficulty.hpp"
#include "GameContext.hpp"


class MineSweeper {
public:
    MineSweeper();
    void run();

private:
    void loadAssets();
    void registerStates();

    sf::RenderWindow mWindow;
    AssetManager mAssets;
    StateManager mStateManager;
    Difficulty mDifficulty;

    GameContext mContext;
};

#endif //MINESWEEPER_MINESWEEPER_HPP
