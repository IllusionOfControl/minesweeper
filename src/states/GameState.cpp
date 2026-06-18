#include <string>
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "../DEFINITIONS.h"

namespace {
    // Indices into tiles.png (see legend in legacy/ANALYSIS.md).
    constexpr int TILE_PRESSED = 0;          // same look as a revealed "0"
    constexpr int TILE_BOMB = 9;
    constexpr int TILE_BOMB_DETONATED = 10;
    constexpr int TILE_CLOSED = 11;
    constexpr int TILE_FLAG = 12;
    constexpr int TILE_QUESTION = 13;
    constexpr int TILE_WRONG_FLAG = 14;

    int tileForCell(const Board &board, int x, int y, Board::Status status, bool pressed) {
        const Board::Cell &cell = board.cellAt(x, y);

        if (status == Board::Status::Lost) {
            if (cell.isDetonated)
                return TILE_BOMB_DETONATED;
            if (cell.isMine && cell.mark == Board::Mark::Flag)
                return TILE_FLAG;
            if (cell.isMine)
                return TILE_BOMB;
            if (cell.mark == Board::Mark::Flag)
                return TILE_WRONG_FLAG;
            if (cell.isRevealed)
                return cell.adjacentMines;
            return TILE_CLOSED;
        }

        if (status == Board::Status::Won) {
            if (cell.isMine)
                return TILE_FLAG;
            if (cell.isRevealed)
                return cell.adjacentMines;
            return TILE_CLOSED;
        }

        // FirstMove / Playing
        if (cell.isRevealed)
            return cell.adjacentMines;
        if (pressed)
            return TILE_PRESSED;
        switch (cell.mark) {
            case Board::Mark::Flag:
                return TILE_FLAG;
            case Board::Mark::Question:
                return TILE_QUESTION;
            default:
                return TILE_CLOSED;
        }
    }
}

GameState::GameState(GameDataRef context)
        : mContext(context), mGuiContainer() {
}

void GameState::init() {
    auto difficulty = mContext->difficulty;
    mContext->window.create(
            sf::VideoMode((difficulty.field_width + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                          (difficulty.field_height + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
            "Minesweeper",
            sf::Style::Titlebar | sf::Style::Close);
    auto windowSize = mContext->window.getSize();

    auto background = std::make_shared<Background>();
    background->setTexture(mContext->assets.getTexture("background"));
    background->setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto mainMenuButton = std::make_shared<Button>();
    mainMenuButton->setTexture(mContext->assets.getTexture("state_buttons"));
    mainMenuButton->setNormalTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setSelectedTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);
    mainMenuButton->setCallback([this]() {
        mContext->manager.addState(StateRef(new MainMenuState(mContext)), true);
    });

    auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(mContext->assets.getTexture("state_buttons"));
    exitButton->setNormalTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setSelectedTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setPosition((float)(difficulty.field_width + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);
    exitButton->setCallback([this]() {
        mContext->window.close();
    });

    mMinesLeftIndicator = std::make_shared<Indicator>();
    mMinesLeftIndicator->setTexture(mContext->assets.getTexture("led_background"));
    mMinesLeftIndicator->setTextureRect({0, 0, SQUARE_SIZE * 3, SQUARE_SIZE});
    mMinesLeftIndicator->setPosition(GAME_BORDER_LEFT * SQUARE_SIZE, (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    mMinesLeftIndicator->setFont(mContext->assets.GetFont("default_font"));

    mTimeLeftIndicator = std::make_shared<Indicator>();
    mTimeLeftIndicator->setTexture(mContext->assets.getTexture("led_background"));
    mTimeLeftIndicator->setTextureRect({0, 0, SQUARE_SIZE * 3, SQUARE_SIZE});
    mTimeLeftIndicator->setPosition((GAME_BORDER_LEFT + difficulty.field_width - 3) * SQUARE_SIZE,
                                    (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    mTimeLeftIndicator->setFont(mContext->assets.GetFont("default_font"));

    bool isSmileSmall = difficulty.field_width % 2 ? true : false;
    mSmileButton = std::make_shared<SmileButton>(isSmileSmall);
    mSmileButton->setTexture(mContext->assets.getTexture("smiles_button"));
    mSmileButton->setPosition(
            (GAME_BORDER_LEFT + difficulty.field_width / 2 - (difficulty.field_width % 2 ? 0 : 1)) * SQUARE_SIZE,
            (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    mSmileButton->setCallback([this]() {
        reset();
    });

    reset();

    mGuiContainer.pack(background);
    mGuiContainer.pack(mainMenuButton);
    mGuiContainer.pack(exitButton);
    mGuiContainer.pack(mMinesLeftIndicator);
    mGuiContainer.pack(mTimeLeftIndicator);
    mGuiContainer.pack(mSmileButton);
}

void GameState::handleInput() {
    sf::Event event;

    while (mContext->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);

        switch (event.type) {
            case sf::Event::Closed:
                mContext->window.close();
                break;

            case sf::Event::MouseButtonPressed: {
                auto cell = cellAt({event.mouseButton.x, event.mouseButton.y});
                if (event.mouseButton.button == sf::Mouse::Left
                    && mBoard->inBounds(cell.x, cell.y)
                    && mBoard->status() == Board::Status::Playing) {
                    mPressedCell = cell.y * mBoard->width() + cell.x;
                    mSmileButton->setReaction(SmileButton::SmileReveal);
                    mNeedToUpdate = true;
                }
                break;
            }

            case sf::Event::MouseButtonReleased: {
                auto cell = cellAt({event.mouseButton.x, event.mouseButton.y});
                mPressedCell = -1;

                if (mBoard->inBounds(cell.x, cell.y)) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (mBoard->status() == Board::Status::FirstMove)
                            mGameClock.restart();
                        mBoard->reveal(cell.x, cell.y);
                        mNeedToUpdate = true;
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        mBoard->toggleMark(cell.x, cell.y);
                        mNeedToUpdate = true;
                    } else if (event.mouseButton.button == sf::Mouse::Middle) {
                        mBoard->chord(cell.x, cell.y);
                        mNeedToUpdate = true;
                    }
                }
                break;
            }

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::R)
                    reset();
                break;

            default:
                break;
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
                break;
            case Board::Status::Lost:
                mSmileButton->setReaction(SmileButton::SmileLose);
                break;
            default:
                if (mPressedCell < 0)
                    mSmileButton->setReaction(SmileButton::SmileUsual);
                break;
        }

        mNeedToUpdate = false;
    }

    if (mBoard->status() == Board::Status::Playing)
        updateTimer();
}

void GameState::reset() {
    auto difficulty = mContext->difficulty;
    mBoard = std::make_unique<Board>(difficulty.field_width, difficulty.field_height, difficulty.bomb_count);

    mPressedCell = -1;
    mGameTime = 0;
    mNeedToUpdate = false;

    mSmileButton->setReaction(SmileButton::SmileUsual);
    mMinesLeftIndicator->setString(std::to_string(mBoard->minesLeft()));
    mTimeLeftIndicator->setString(std::to_string(mGameTime));

    initGridCells();
}

void GameState::draw() {
    mContext->window.clear(sf::Color::Red);

    mContext->window.draw(mGuiContainer);

    for (auto &cell: mGridCells) {
        mContext->window.draw(cell);
    }

    mContext->window.display();
}

void GameState::initGridCells() {
    mGridCells.clear();

    auto &texture = mContext->assets.getTexture("tile_texture");
    for (int y = 0; y < mBoard->height(); ++y) {
        for (int x = 0; x < mBoard->width(); ++x) {
            sf::Sprite cell;
            cell.setTexture(texture);
            cell.setTextureRect(TILE_INT_RECT(TILE_CLOSED));
            cell.setPosition((GAME_BORDER_LEFT + x) * SQUARE_SIZE,
                             (GAME_BORDER_TOP + y) * SQUARE_SIZE);
            mGridCells.push_back(cell);
        }
    }
}

void GameState::renderCells() {
    const Board::Status status = mBoard->status();
    for (int y = 0; y < mBoard->height(); ++y) {
        for (int x = 0; x < mBoard->width(); ++x) {
            const int i = y * mBoard->width() + x;
            const bool pressed = (i == mPressedCell);
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(tileForCell(*mBoard, x, y, status, pressed)));
        }
    }
}

void GameState::updateTimer() {
    mGameTimer = mGameClock.getElapsedTime();
    if (mGameTimer.asSeconds() > mGameTime) {
        if (mGameTime < 999) {
            mGameTime++;
            mTimeLeftIndicator->setString(std::to_string(mGameTime));
        }
    }
}

sf::Vector2i GameState::cellAt(sf::Vector2i pixel) const {
    sf::IntRect field(GAME_BORDER_LEFT * SQUARE_SIZE,
                      GAME_BORDER_TOP * SQUARE_SIZE,
                      mBoard->width() * SQUARE_SIZE,
                      mBoard->height() * SQUARE_SIZE);
    if (!field.contains(pixel))
        return {-1, -1};

    return {(pixel.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE,
            (pixel.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE};
}
