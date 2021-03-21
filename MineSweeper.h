#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

#include <memory>
#include "managers/AssetManager.h"
#include "managers/InputManager.h"
#include "managers/StateManager.h"
#include "DEFINITIONS.h"

struct DifficultyData {
    int field_width;
    int field_height;
    int bomb_count;
};

struct GameData
{
    StateManager manager;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
    DifficultyData difficulty = DIFFICULTY_EASY;
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
