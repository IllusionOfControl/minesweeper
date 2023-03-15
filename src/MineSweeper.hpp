#ifndef MINESWEEPER_MINESWEEPER_HPP
#define MINESWEEPER_MINESWEEPER_HPP

#include <memory>
#include "managers/AssetManager.hpp"
#include "managers/StateManager.hpp"
#include "managers/LeaderboardManager.hpp"
#include "DEFINITIONS.h"

struct DifficultyData {
    int field_width;
    int field_height;
    int bomb_count;
    int difficulty_type;
};

struct GameData
{
    StateManager manager;
    sf::RenderWindow window;
    AssetManager assets;
    DifficultyData difficulty;
    LeaderboardManager leaderboard;
    struct Record lastResults;
};

typedef std::shared_ptr<GameData> GameDataRef;

class MineSweeper {
public:
    MineSweeper();

private:
    GameDataRef _data = std::make_shared<GameData>();

    void Run();
};


#endif //MINESWEEPER_MINESWEEPER_HPP
