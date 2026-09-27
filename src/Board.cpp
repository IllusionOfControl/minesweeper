#include "Board.hpp"

#include <algorithm>
#include <stack>
#include <utility>

Board::Board(const int width, const int height, const int mineCount)
    : mWidth(width)
      , mHeight(height)
      , mMineCount(mineCount)
      , mRng(std::random_device{}()) { reset(); }

void Board::reset() {
    mCells.assign(static_cast<std::size_t>(mWidth) * mHeight, Cell{});
    mFlagsPlaced = 0;
    mRevealedSafeCount = 0;
    mStatus = Status::FirstMove;
}

bool Board::inBounds(const int x, const int y) const { return x >= 0 && x < mWidth && y >= 0 && y < mHeight; }

const Board::Cell& Board::cellAt(const int x, const int y) const { return mCells.at(index(x, y)); }

void Board::placeMines(const int safeX, const int safeY) {
    const int safe = index(safeX, safeY);
    const int total = mWidth * mHeight;

    std::vector<int> candidates;
    candidates.reserve(total - 1);
    for (int i = 0; i < total; ++i) {
        if (i != safe)
            candidates.push_back(i);
    }

    std::shuffle(candidates.begin(), candidates.end(), mRng);

    const int mines = std::min(mMineCount, static_cast<int>(candidates.size()));
    for (int k = 0; k < mines; ++k)
        mCells[candidates[k]].isMine = true;

    for (int y = 0; y < mHeight; ++y) {
        for (int x = 0; x < mWidth; ++x) {
            if (mCells[index(x, y)].isMine)
                continue;

            int count = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0)
                        continue;
                    const int nx = x + dx;
                    const int ny = y + dy;
                    if (inBounds(nx, ny) && mCells[index(nx, ny)].isMine)
                        ++count;
                }
            }
            mCells[index(x, y)].adjacentMines = count;
        }
    }
}

void Board::reveal(const int x, const int y) {
    if (mStatus == Status::Won || mStatus == Status::Lost)
        return;
    if (!inBounds(x, y))
        return;

    if (mStatus == Status::FirstMove) {
        placeMines(x, y);
        mStatus = Status::Playing;
    }

    Cell& cell = mCells[index(x, y)];
    if (cell.isRevealed || cell.mark == Mark::Flag)
        return;

    if (cell.isMine) {
        cell.isRevealed = true;
        cell.isDetonated = true;
        mStatus = Status::Lost;
        return;
    }

    revealFloodFill(x, y);

    if (mRevealedSafeCount == mWidth * mHeight - mMineCount)
        mStatus = Status::Won;
}

void Board::revealFloodFill(int startX, int startY) {
    std::stack<std::pair<int, int>> pending;
    pending.emplace(startX, startY);

    while (!pending.empty()) {
        const auto [x, y] = pending.top();
        pending.pop();

        Cell& cell = mCells[index(x, y)];
        if (cell.isRevealed || cell.mark == Mark::Flag || cell.isMine)
            continue;

        cell.isRevealed = true;
        cell.mark = Mark::None;
        ++mRevealedSafeCount;

        if (cell.adjacentMines != 0)
            continue;

        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0)
                    continue;
                const int nx = x + dx;
                const int ny = y + dy;
                if (!inBounds(nx, ny))
                    continue;
                if (const Cell& neighbour = mCells[index(nx, ny)]; !neighbour.isRevealed && neighbour.mark != Mark::Flag
                    && !neighbour.isMine)
                    pending.emplace(nx, ny);
            }
        }
    }
}

void Board::toggleMark(int x, int y) {
    if (mStatus != Status::Playing)
        return;
    if (!inBounds(x, y))
        return;

    Cell& cell = mCells[index(x, y)];
    if (cell.isRevealed)
        return;

    switch (cell.mark) {
        case Mark::None:
            cell.mark = Mark::Flag;
            ++mFlagsPlaced;
            break;
        case Mark::Flag:
            cell.mark = Mark::Question;
            --mFlagsPlaced;
            break;
        case Mark::Question:
            cell.mark = Mark::None;
            break;
    }
}

void Board::chord(const int x, const int y) {
    if (mStatus != Status::Playing)
        return;
    if (!inBounds(x, y))
        return;

    const Cell& cell = mCells[index(x, y)];
    if (!cell.isRevealed || cell.isMine || cell.adjacentMines == 0)
        return;

    int flagged = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0)
                continue;
            const int nx = x + dx;
            const int ny = y + dy;
            if (inBounds(nx, ny) && mCells[index(nx, ny)].mark == Mark::Flag)
                ++flagged;
        }
    }

    if (flagged != cell.adjacentMines)
        return;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0)
                continue;
            const int nx = x + dx;
            const int ny = y + dy;
            if (!inBounds(nx, ny))
                continue;
            if (const Cell& neighbour = mCells[index(nx, ny)]; neighbour.mark != Mark::Flag && !neighbour.isRevealed)
                reveal(nx, ny);
            if (mStatus == Status::Lost)
                return;
        }
    }
}
