#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

#include <memory>
#include "managers/AssetManager.h"
#include "managers/InputManager.h"
#include "managers/StateManager.h"


struct GameData
{
    StateManager machine;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
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
