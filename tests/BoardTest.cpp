#include <catch2/catch_test_macros.hpp>

#include "Board.hpp"

namespace {
    int countMines(const Board &b) {
        int n = 0;
        for (int y = 0; y < b.height(); ++y)
            for (int x = 0; x < b.width(); ++x)
                if (b.cellAt(x, y).isMine)
                    ++n;
        return n;
    }

    int countNeighbourMines(const Board &b, int x, int y) {
        int n = 0;
        for (int dy = -1; dy <= 1; ++dy)
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0)
                    continue;
                if (b.inBounds(x + dx, y + dy) && b.cellAt(x + dx, y + dy).isMine)
                    ++n;
            }
        return n;
    }
}

TEST_CASE("a fresh board has no mines placed and full mine counter") {
    Board b(9, 9, 10);
    REQUIRE(b.status() == Board::Status::FirstMove);
    REQUIRE(b.minesLeft() == 10);
    REQUIRE(countMines(b) == 0);
}

TEST_CASE("first reveal is always safe and places all mines (L2)") {
    Board b(9, 9, 10);

    b.reveal(4, 4);

    REQUIRE(b.status() != Board::Status::Lost);
    REQUIRE_FALSE(b.cellAt(4, 4).isMine);
    REQUIRE(b.cellAt(4, 4).isRevealed);
    REQUIRE(countMines(b) == 10);
}

TEST_CASE("adjacent mine counts are consistent with the layout") {
    Board b(12, 10, 20);
    b.reveal(0, 0);

    for (int y = 0; y < b.height(); ++y)
        for (int x = 0; x < b.width(); ++x) {
            const Board::Cell &c = b.cellAt(x, y);
            if (c.isMine)
                continue;
            REQUIRE(c.adjacentMines == countNeighbourMines(b, x, y));
        }
}

TEST_CASE("flood fill reveals the border of every empty cell (B3)") {
    Board b(16, 16, 10);
    b.reveal(0, 0);

    for (int y = 0; y < b.height(); ++y)
        for (int x = 0; x < b.width(); ++x) {
            const Board::Cell &c = b.cellAt(x, y);
            if (c.isRevealed)
                REQUIRE_FALSE(c.isMine);
            if (c.isRevealed && c.adjacentMines == 0) {
                for (int dy = -1; dy <= 1; ++dy)
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (b.inBounds(x + dx, y + dy))
                            REQUIRE(b.cellAt(x + dx, y + dy).isRevealed);
                    }
            }
        }
}

TEST_CASE("revealing a large sparse board completes without recursion overflow") {
    Board b(30, 16, 1);
    b.reveal(0, 0);
    REQUIRE(b.status() != Board::Status::Lost);
}

TEST_CASE("marks cycle None -> Flag -> Question -> None and track mines-left (L5)") {
    Board b(9, 9, 10);
    b.reveal(4, 4); // enter Playing

    int fx = -1, fy = -1;
    for (int y = 0; y < b.height() && fx < 0; ++y)
        for (int x = 0; x < b.width(); ++x)
            if (!b.cellAt(x, y).isRevealed) {
                fx = x;
                fy = y;
                break;
            }
    REQUIRE(fx >= 0);

    const int before = b.minesLeft();

    b.toggleMark(fx, fy);
    REQUIRE(b.cellAt(fx, fy).mark == Board::Mark::Flag);
    REQUIRE(b.minesLeft() == before - 1);

    b.toggleMark(fx, fy);
    REQUIRE(b.cellAt(fx, fy).mark == Board::Mark::Question);
    REQUIRE(b.minesLeft() == before);

    b.toggleMark(fx, fy);
    REQUIRE(b.cellAt(fx, fy).mark == Board::Mark::None);
}

TEST_CASE("chord reveals remaining neighbours when flags match the number (L3)") {
    bool tested = false;

    for (int attempt = 0; attempt < 200 && !tested; ++attempt) {
        Board b(9, 9, 10);
        b.reveal(4, 4);
        if (b.status() != Board::Status::Playing)
            continue;

        for (int y = 0; y < b.height() && !tested; ++y)
            for (int x = 0; x < b.width() && !tested; ++x) {
                const Board::Cell &c = b.cellAt(x, y);
                if (!c.isRevealed || c.adjacentMines == 0)
                    continue;

                bool hasHiddenSafeNeighbour = false;
                for (int dy = -1; dy <= 1; ++dy)
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (!b.inBounds(x + dx, y + dy))
                            continue;
                        const Board::Cell &n = b.cellAt(x + dx, y + dy);
                        if (!n.isMine && !n.isRevealed)
                            hasHiddenSafeNeighbour = true;
                    }
                if (!hasHiddenSafeNeighbour)
                    continue;

                // Flag exactly the mine neighbours, then chord.
                for (int dy = -1; dy <= 1; ++dy)
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (!b.inBounds(x + dx, y + dy))
                            continue;
                        if (b.cellAt(x + dx, y + dy).isMine)
                            b.toggleMark(x + dx, y + dy);
                    }

                b.chord(x, y);

                REQUIRE(b.status() != Board::Status::Lost);
                for (int dy = -1; dy <= 1; ++dy)
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (!b.inBounds(x + dx, y + dy))
                            continue;
                        const Board::Cell &n = b.cellAt(x + dx, y + dy);
                        if (!n.isMine && n.mark != Board::Mark::Flag)
                            REQUIRE(n.isRevealed);
                    }
                tested = true;
            }
    }

    REQUIRE(tested);
}

TEST_CASE("chord with a misplaced flag detonates a mine (L3)") {
    bool tested = false;

    for (int attempt = 0; attempt < 200 && !tested; ++attempt) {
        Board b(9, 9, 10);
        b.reveal(4, 4);
        if (b.status() != Board::Status::Playing)
            continue;

        for (int y = 0; y < b.height() && !tested; ++y)
            for (int x = 0; x < b.width() && !tested; ++x) {
                const Board::Cell &c = b.cellAt(x, y);
                if (!c.isRevealed || c.adjacentMines != 1)
                    continue;

                int wx = -1, wy = -1;
                for (int dy = -1; dy <= 1; ++dy)
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (!b.inBounds(x + dx, y + dy))
                            continue;
                        const Board::Cell &n = b.cellAt(x + dx, y + dy);
                        if (!n.isMine && !n.isRevealed) {
                            wx = x + dx;
                            wy = y + dy;
                        }
                    }
                if (wx < 0)
                    continue;

                // Flag the wrong (safe) neighbour: count now matches the "1",
                // but the real mine stays unflagged.
                b.toggleMark(wx, wy);
                b.chord(x, y);

                REQUIRE(b.status() == Board::Status::Lost);
                tested = true;
            }
    }

    REQUIRE(tested);
}

TEST_CASE("revealing every safe cell wins the game") {
    Board b(4, 4, 2);
    b.reveal(0, 0);

    for (int y = 0; y < b.height(); ++y)
        for (int x = 0; x < b.width(); ++x)
            if (!b.cellAt(x, y).isMine && !b.cellAt(x, y).isRevealed)
                b.reveal(x, y);

    REQUIRE(b.status() == Board::Status::Won);
}

TEST_CASE("reset returns the board to a fresh state (L4)") {
    Board b(9, 9, 10);
    b.reveal(4, 4);
    b.toggleMark(0, 0);

    b.reset();

    REQUIRE(b.status() == Board::Status::FirstMove);
    REQUIRE(b.minesLeft() == 10);
    REQUIRE(countMines(b) == 0);

    int revealed = 0;
    for (int y = 0; y < b.height(); ++y)
        for (int x = 0; x < b.width(); ++x)
            if (b.cellAt(x, y).isRevealed)
                ++revealed;
    REQUIRE(revealed == 0);
}

TEST_CASE("out-of-bounds operations are safe and ignored") {
    Board b(9, 9, 10);
    REQUIRE_NOTHROW(b.reveal(-1, 0));
    REQUIRE_NOTHROW(b.reveal(0, -1));
    REQUIRE_NOTHROW(b.reveal(9, 0));
    REQUIRE_NOTHROW(b.reveal(0, 9));
    REQUIRE(b.status() == Board::Status::FirstMove);

    b.reveal(0, 0); // enter Playing
    REQUIRE_NOTHROW(b.toggleMark(-1, 0));
    REQUIRE_NOTHROW(b.toggleMark(100, 100));
    REQUIRE_NOTHROW(b.chord(-5, -5));
    REQUIRE_NOTHROW(b.chord(50, 50));
}

TEST_CASE("flagged cells cannot be revealed directly") {
    Board b(9, 9, 10);
    b.reveal(0, 0);

    int targetX = -1, targetY = -1;
    for (int y = 0; y < b.height() && targetX < 0; ++y) {
        for (int x = 0; x < b.width(); ++x) {
            if (!b.cellAt(x, y).isRevealed) {
                targetX = x;
                targetY = y;
                break;
            }
        }
    }
    REQUIRE(targetX >= 0);

    b.toggleMark(targetX, targetY); // Flag
    REQUIRE(b.cellAt(targetX, targetY).mark == Board::Mark::Flag);

    b.reveal(targetX, targetY);
    REQUIRE_FALSE(b.cellAt(targetX, targetY).isRevealed);
}

TEST_CASE("operations are ignored once game is lost or won") {
    Board b(4, 4, 1);
    b.reveal(0, 0);

    // Find the mine and reveal it to trigger Lost
    int mineX = -1, mineY = -1;
    for (int y = 0; y < b.height(); ++y) {
        for (int x = 0; x < b.width(); ++x) {
            if (b.cellAt(x, y).isMine) {
                mineX = x;
                mineY = y;
                break;
            }
        }
    }
    REQUIRE(mineX >= 0);

    b.reveal(mineX, mineY);
    REQUIRE(b.status() == Board::Status::Lost);
    REQUIRE(b.cellAt(mineX, mineY).isDetonated);
    REQUIRE(b.cellAt(mineX, mineY).isRevealed);

    // Further operations must not change state
    const int flagsBefore = b.minesLeft();
    b.toggleMark(0, 0);
    REQUIRE(b.minesLeft() == flagsBefore);
    b.reveal(0, 0);
    REQUIRE(b.status() == Board::Status::Lost);
}
