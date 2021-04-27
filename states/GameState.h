#ifndef MINESWEEPER_GAMESTATE_H
#define MINESWEEPER_GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "RecordSaveState.h"
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

    void Reset();
    void RevealCell(int x, int y);
    void MarkCell(int x, int y);
    void UpdateSmile(sf::Texture);

    GameDataRef _data;

    sf::Sprite _background;
    sf::Sprite _gridSprite;
    sf::Sprite _smileButton;

    sf::Sprite _minesLeftSprite;
    sf::Text _minesLeftText;

    sf::Sprite _gameTimerSprite;
    sf::Text _gameTimerText;

    sf::Sprite _mainMenuButton;
    sf::Sprite _exitButton;

    std::vector<sf::Sprite> _gridCells;
    std::vector<int> _gridArray;

    bool _isUpdate;
    bool _isSmileSmall;

    int _cellsRevealed;
    int _minesCount;
    int _gameState;
    int _gameTime;
    int _smileReaction;

    sf::Clock _gameClock;
    sf::Time _gameTimer;
};


#endif //MINESWEEPER_GAMESTATE_H
