#ifndef MINESWEEPER_GAMESTATE_H
#define MINESWEEPER_GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "../MineSweeper.h"

class GameState : public State
{
public:
    GameState(GameDataRef data);

    void Init() override;

    void HandleInput() override;
    void Update() override;
    void Draw() override;

private:
    void InitGridCells();
    void InitGridArray(int x, int y);

    void RevealCell(int x, int y);
    void MarkCell(int x, int y);

    GameDataRef _data;

    sf::Sprite _background;
    sf::Sprite _pauseButton;
    sf::Sprite _gridSprite;

    sf::Sprite _mainMenuButton;
    sf::Sprite _exitButton;

    std::vector<sf::Sprite> _gridCells;
    std::vector<int> _gridArray;

    bool _isUpdate;
    bool _isFirstMove;

    int _cellsRevealed;
    int _minesCount;
    int _gameState;  // ?

    sf::Clock _clock;
};


#endif //MINESWEEPER_GAMESTATE_H
