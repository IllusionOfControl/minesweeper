#ifndef MINESWEEPER_GAMESTATE_HPP
#define MINESWEEPER_GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "../MineSweeper.hpp"
#include "../gui/Background.hpp"
#include "../gui/Container.hpp"
#include "../gui/Indicator.hpp"
#include "../gui/Button.hpp"
#include "../gui/SmileButton.hpp"

class GameState : public State {
public:
    enum State {
        GameFirstMove,
        GamePlaying,
        GameWon,
        GameLose
    };
    enum CellState {
        CellEmpty,
        CellBomb,
        CellBombDetonated,
        CellFlag,
        CellQuestion,
        CellRevealed,
        CellSelected
    };

public:
    explicit GameState(GameDataRef context);

    void Init() override;

    void HandleInput() override;

    void Update() override;

    void Draw() override;

private:
    void initGridCells();

    void initGridArray(int x, int y);

    void reset();

    void revealCell(int x, int y);

    void markCell(int x, int y);

    void updateGridCells();
    void updateGridCellsOnLose();
    void updateGridCellsOnWin();
    void updateTimer();
    void checkOnWin();

    void selectCellsArea(int col, int row);

private:
    GameDataRef mContext;

    sf::Sprite mGridSprite;

    std::vector<sf::Sprite> mGridCells;
    std::vector<int> mGridArray;

    State mGameState;

    bool mNeedToUpdate;

    int mCellsRevealed;
    int mMinesCount;
    int mGameTime;

    sf::Clock mGameClock;   // ??
    sf::Time mGameTimer;

    Container mGuiContainer;
    Indicator::Ptr mMinesLeftIndicator;
    Indicator::Ptr mTimeLeftIndicator;
    SmileButton::Ptr mSmileButton;
};

#endif //MINESWEEPER_GAMESTATE_HPP
