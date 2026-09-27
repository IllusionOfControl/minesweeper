#ifndef MINESWEEPER_BOARD_HPP
#define MINESWEEPER_BOARD_HPP

#include <random>
#include <vector>

class Board {
public:
    enum class Status {
        FirstMove,
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
        int adjacentMines = 0;
        bool isMine = false;
        bool isRevealed = false;
        bool isDetonated = false;
        Mark mark = Mark::None;
    };

    Board(int width, int height, int mineCount);

    void reset();

    void reveal(int x, int y);

    void toggleMark(int x, int y);

    void chord(int x, int y);

    Status status() const { return mStatus; }
    int width() const { return mWidth; }
    int height() const { return mHeight; }
    int mineCount() const { return mMineCount; }

    int minesLeft() const { return mMineCount - mFlagsPlaced; }

    const Cell& cellAt(int x, int y) const;

    bool inBounds(int x, int y) const;

private:
    int index(const int x, const int y) const { return y * mWidth + x; }

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
