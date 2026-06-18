#ifndef MINESWEEPER_BOARD_HPP
#define MINESWEEPER_BOARD_HPP

#include <random>
#include <vector>

// Pure Minesweeper game logic, free of any rendering/SFML dependency so it can
// be unit-tested in isolation.
class Board {
public:
    enum class Status {
        FirstMove,  // no mines placed yet; first reveal is always safe
        Playing,
        Won,
        Lost
    };

    enum class Mark {
        None,
        Flag,
        Question
    };

    struct Cell {
        int adjacentMines = 0;     // number of mines in the 8 neighbours (0..8)
        bool isMine = false;
        bool isRevealed = false;
        bool isDetonated = false;  // the mine the player stepped on
        Mark mark = Mark::None;
    };

    Board(int width, int height, int mineCount);

    // Reset to a fresh, unstarted board with the same dimensions.
    void reset();

    // Reveal a cell. The very first reveal places the mines so the clicked cell
    // is guaranteed safe (only that cell - see L2 in legacy/ANALYSIS.md).
    void reveal(int x, int y);

    // Cycle a hidden cell None -> Flag -> Question -> None.
    void toggleMark(int x, int y);

    // "Chord": on a revealed number whose flagged-neighbour count matches the
    // number, reveal all remaining non-flagged neighbours at once.
    void chord(int x, int y);

    Status status() const { return mStatus; }
    int width() const { return mWidth; }
    int height() const { return mHeight; }
    int mineCount() const { return mMineCount; }

    // Mines minus placed flags. May be negative (no artificial cap - see L5).
    int minesLeft() const { return mMineCount - mFlagsPlaced; }

    const Cell &cellAt(int x, int y) const;

    bool inBounds(int x, int y) const;

private:
    int index(int x, int y) const { return y * mWidth + x; }

    void placeMines(int safeX, int safeY);
    void revealFloodFill(int startX, int startY);

    int mWidth;
    int mHeight;
    int mMineCount;
    int mFlagsPlaced = 0;
    int mRevealedSafeCount = 0;
    Status mStatus = Status::FirstMove;
    std::vector<Cell> mCells;
    std::mt19937 mRng;
};

#endif // MINESWEEPER_BOARD_HPP
