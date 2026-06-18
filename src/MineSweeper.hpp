#ifndef MINESWEEPER_MINESWEEPER_HPP
#define MINESWEEPER_MINESWEEPER_HPP

#include <memory>
#include "managers/AssetManager.hpp"
#include "managers/StateManager.hpp"
#include "DEFINITIONS.h"

struct DifficultyData {
    int field_width;
    int field_height;
    int bomb_count;
};

constexpr DifficultyData DIFFICULTY_EASY{9, 9, 10};
constexpr DifficultyData DIFFICULTY_MEDIUM{16, 16, 40};
constexpr DifficultyData DIFFICULTY_HARD{32, 16, 99};

struct Context
{
    StateManager manager;
    sf::RenderWindow window;
    AssetManager assets;
    DifficultyData difficulty;
};

typedef std::shared_ptr<Context> GameDataRef;

class MineSweeper {
public:
    MineSweeper();

private:
    GameDataRef mData = std::make_shared<Context>();

    void run();
};


#endif //MINESWEEPER_MINESWEEPER_HPP
