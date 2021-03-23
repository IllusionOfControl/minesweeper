#ifndef MINESWEEPER_GAMESTATE_H
#define MINESWEEPER_GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "../MineSweeper.h"

class GameState : public State
{
public:
    GameState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();

private:
    void InitGridCells();
    void InitGridArray(int firstMove);

    void CheckAndPlacePiece();

    void CheckHasPlayerWon(int turn);
    void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);

    GameDataRef _data;

    sf::Sprite _background;

    sf::Sprite _pauseButton;

    sf::Sprite _gridSprite;

    std::vector<sf::Sprite> _gridCells;
    std::vector<int> _gridArray;

    int minesCount;
    int gameState;  // ?

    sf::Clock _clock;
};


#endif //MINESWEEPER_GAMESTATE_H
