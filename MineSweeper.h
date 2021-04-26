#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

#include <memory>
#include "managers/AssetManager.h"
#include "managers/StateManager.h"
#include "managers/LeaderboardManager.h"
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
};

typedef std::shared_ptr<GameData> GameDataRef;

class MineSweeper {
public:
    MineSweeper();

private:
    GameDataRef _data = std::make_shared<GameData>();

    void Run();
};


#endif //MINESWEEPER_MINESWEEPER_H
