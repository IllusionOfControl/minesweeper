#include "GameState.hpp"

#include <algorithm>
#include <string>
#include "GameContext.hpp"
#include "Layout.hpp"
#include "WindowUtils.hpp"
#include "gui/TopBar.hpp"
#include "managers/ResourceIdentifiers.hpp"

namespace {
    constexpr int TILE_PRESSED = 0;
    constexpr int TILE_BOMB = 9;
    constexpr int TILE_BOMB_DETONATED = 10;
    constexpr int TILE_CLOSED = 11;
    constexpr int TILE_FLAG = 12;
    constexpr int TILE_QUESTION = 13;
    constexpr int TILE_WRONG_FLAG = 14;

    int tileForCell(const Board& board, const int x, const int y, const Board::Status status, const bool pressed) {
        const auto& [adjacentMines, isMine, isRevealed, isDetonated, mark] = board.cellAt(x, y);

        if (isRevealed) {
            if (isMine) {
                return isDetonated ? TILE_BOMB_DETONATED : TILE_BOMB;
            }
            return adjacentMines;
        }

        if (status == Board::Status::Lost) {
            if (isMine && mark != Board::Mark::Flag) {
                return TILE_BOMB;
            }
            if (!isMine && mark == Board::Mark::Flag) {
                return TILE_WRONG_FLAG;
            }
        }

        switch (mark) {
            case Board::Mark::Flag:
                return TILE_FLAG;
            case Board::Mark::Question:
                return TILE_QUESTION;
            case Board::Mark::None:
            default:
                return pressed ? TILE_PRESSED : TILE_CLOSED;
        }
    }
}

GameState::GameState(GameContext& context)
    : State(context) {}

void GameState::init() {
    const auto& difficulty = getContext().difficulty;
    const int boardWidth = difficulty.getWidth();
    const int boardHeight = difficulty.getHeight();

    const int windowTilesX = boardWidth + 2;
    const int windowTilesY = boardHeight + 5;

    const auto windowSize = Layout::toWindowSize(windowTilesX, windowTilesY);
    resizeWindow(getContext().window, windowSize);

    auto& backgroundTexture = getContext().assets.getTexture(TextureID::Background);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect(Layout::getRect(0, 0, windowTilesX, windowTilesY));

    const auto topBar = std::make_shared<TopBar>(getContext(), windowTilesX);

    const auto& ledTexture = getContext().assets.getTexture(TextureID::LedBackground);
    const auto& font = getContext().assets.getFont(FontID::Default);

    mMinesLeftIndicator = std::make_shared<Indicator>();
    mMinesLeftIndicator->setTexture(ledTexture);
    mMinesLeftIndicator->setTextureRect(Layout::getRect(0, 0, 3, 1));
    mMinesLeftIndicator->setPosition(Layout::toPixels(1, 2));
    mMinesLeftIndicator->setFont(font);

    mTimeLeftIndicator = std::make_shared<Indicator>();
    mTimeLeftIndicator->setTexture(ledTexture);
    mTimeLeftIndicator->setTextureRect(Layout::getRect(0, 0, 3, 1));
    mTimeLeftIndicator->setPosition(Layout::toPixels(boardWidth - 2, 2));
    mTimeLeftIndicator->setFont(font);

    const bool isSmileSmall = (boardWidth % 2 != 0);
    mSmileButton = std::make_shared<SmileButton>(isSmileSmall);
    mSmileButton->setTexture(getContext().assets.getTexture(TextureID::Smiles));

    const int smileTileX = 1 + boardWidth / 2 - (isSmileSmall ? 0 : 1);
    mSmileButton->setPosition(Layout::toPixels(smileTileX, 2));
    mSmileButton->setCallback([this]() { reset(); });

    mGuiContainer.pack(topBar);
    mGuiContainer.pack(mMinesLeftIndicator);
    mGuiContainer.pack(mTimeLeftIndicator);
    mGuiContainer.pack(mSmileButton);

    reset();
}

void GameState::handleInput() {
    while (const std::optional<sf::Event> event = getContext().window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            getContext().window.close();
            return;
        }

        mGuiContainer.handleEvent(*event);

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (const auto cell = cellAt({mousePressed->position.x, mousePressed->position.y}); mousePressed->button == sf::Mouse::Button::Left
                && mBoard->inBounds(cell.x, cell.y)
                && mBoard->status() == Board::Status::Playing) {
                mPressedCell = cell.y * mBoard->width() + cell.x;
                mSmileButton->setReaction(SmileButton::SmileReveal);
                mNeedToUpdate = true;
            }
        } else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            const auto cell = cellAt({mouseReleased->position.x, mouseReleased->position.y});
            mPressedCell = -1;

            if (mBoard->inBounds(cell.x, cell.y)) {
                if (mouseReleased->button == sf::Mouse::Button::Left) {
                    if (mBoard->status() == Board::Status::FirstMove) {
                        mGameClock.restart();
                    }
                    mBoard->reveal(cell.x, cell.y);
                    mNeedToUpdate = true;
                } else if (mouseReleased->button == sf::Mouse::Button::Right) {
                    mBoard->toggleMark(cell.x, cell.y);
                    mNeedToUpdate = true;
                } else if (mouseReleased->button == sf::Mouse::Button::Middle) {
                    mBoard->chord(cell.x, cell.y);
                    mNeedToUpdate = true;
                }
            }
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::R) {
                reset();
            }
        }
    }
}

void GameState::update() {
    if (mNeedToUpdate) {
        renderCells();
        mMinesLeftIndicator->setString(std::to_string(mBoard->minesLeft()));

        switch (mBoard->status()) {
            case Board::Status::Won:
                mSmileButton->setReaction(SmileButton::SmileWin);
                if (!mGameWon) {
                    mGameWon = true;
                    mWinDelayClock.restart();

                    const auto& difficulty = getContext().difficulty;
                    GameResult result;
                    result.won = true;
                    result.timeSeconds = mGameTime;
                    result.difficulty = toString(difficulty.getPreset());
                    result.width = difficulty.getWidth();
                    result.height = difficulty.getHeight();
                    result.mines = difficulty.getMineCount();
                    result.date = ResultManager::getCurrentDateTime();
                    getContext().lastResult = result;
                }
                break;
            case Board::Status::Lost:
                mSmileButton->setReaction(SmileButton::SmileLose);
                break;
            default:
                if (mPressedCell < 0) {
                    mSmileButton->setReaction(SmileButton::SmileUsual);
                }
                break;
        }

        mNeedToUpdate = false;
    }

    if (mGameWon && mWinDelayClock.getElapsedTime().asSeconds() > 1.2f) {
        getContext().states.changeState(StateID::SaveResult);
        return;
    }

    if (mBoard->status() == Board::Status::Playing) {
        updateTimer();
    }
}

void GameState::reset() {
    const auto& difficulty = getContext().difficulty;
    mBoard = std::make_unique<Board>(difficulty.getWidth(), difficulty.getHeight(), difficulty.getMineCount());

    mPressedCell = -1;
    mGameTime = 0;
    mNeedToUpdate = false;
    mGameWon = false;

    mSmileButton->setReaction(SmileButton::SmileUsual);
    mMinesLeftIndicator->setString(std::to_string(mBoard->minesLeft()));
    mTimeLeftIndicator->setString(std::to_string(mGameTime));

    initGridCells();
}

void GameState::draw() {
    getContext().window.clear(sf::Color::Red);

    getContext().window.draw(mBackground);
    getContext().window.draw(mGuiContainer);

    for (const auto& cell : mGridCells) {
        getContext().window.draw(cell);
    }

    getContext().window.display();
}

void GameState::initGridCells() {
    mGridCells.clear();
    mGridCells.reserve(static_cast<std::size_t>(mBoard->width() * mBoard->height()));

    const auto& texture = getContext().assets.getTexture(TextureID::Tiles);
    for (int y = 0; y < mBoard->height(); ++y) {
        for (int x = 0; x < mBoard->width(); ++x) {
            sf::Sprite cell(texture);
            cell.setTextureRect(Layout::getRect(TILE_CLOSED, 0, 1, 1));
            cell.setPosition(Layout::toPixels(1 + x, 4 + y));
            mGridCells.push_back(std::move(cell));
        }
    }
}

void GameState::renderCells() {
    const Board::Status status = mBoard->status();
    for (int y = 0; y < mBoard->height(); ++y) {
        for (int x = 0; x < mBoard->width(); ++x) {
            const int i = y * mBoard->width() + x;
            const bool pressed = (i == mPressedCell);
            const int tileIndex = tileForCell(*mBoard, x, y, status, pressed);
            mGridCells[static_cast<std::size_t>(i)].setTextureRect(Layout::getRect(tileIndex, 0, 1, 1));
        }
    }
}

void GameState::updateTimer() {
    const int elapsedSeconds = static_cast<int>(mGameClock.getElapsedTime().asSeconds());
    if (elapsedSeconds > mGameTime) {
        if (mGameTime < 999) {
            mGameTime = std::min(elapsedSeconds, 999);
            mTimeLeftIndicator->setString(std::to_string(mGameTime));
        }
    }
}

sf::Vector2i GameState::cellAt(const sf::Vector2i pixel) const {
    const sf::IntRect field(
        sf::Vector2i(Layout::TileSize, 4 * Layout::TileSize),
        sf::Vector2i(mBoard->width() * Layout::TileSize, mBoard->height() * Layout::TileSize)
    );
    if (!field.contains(pixel)) {
        return {-1, -1};
    }

    return {
        (pixel.x - Layout::TileSize) / Layout::TileSize,
        (pixel.y - 4 * Layout::TileSize) / Layout::TileSize
    };
}
