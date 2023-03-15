#include <iostream>
#include <string>
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "../DEFINITIONS.h"

GameState::GameState(GameDataRef context)
        : mContext(context), mGuiContainer(), mGameState(GameState::State::GameFirstMove) {

}

void GameState::Init() {
    auto difficulty = mContext->difficulty;
    mContext->window.create(
            sf::VideoMode((difficulty.field_width + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                          (difficulty.field_height + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
            "Minesweeper",
            sf::Style::Titlebar | sf::Style::Close);
    auto windowSize = mContext->window.getSize();

    auto background = std::make_shared<Background>();
    background->setTexture(mContext->assets.GetTexture("background"));
    background->setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto mainMenuButton = std::make_shared<Button>();
    mainMenuButton->setTexture(mContext->assets.GetTexture("state_buttons"));
    mainMenuButton->setNormalTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setSelectedTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);
    mainMenuButton->setCallback([&]() {
        mContext->manager.AddState(StateRef(new MainMenuState(mContext)), true);
    });

    auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(mContext->assets.GetTexture("state_buttons"));
    exitButton->setNormalTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setSelectedTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setPosition((difficulty.field_width + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);
    exitButton->setCallback([&]() {
        mContext->window.close();
    });

    mMinesLeftIndicator = std::make_shared<Indicator>();
    mMinesLeftIndicator->setTexture(mContext->assets.GetTexture("led_background"));
    mMinesLeftIndicator->setTextureRect({0, 0, SQUARE_SIZE * 3, SQUARE_SIZE});
    mMinesLeftIndicator->setPosition(GAME_BORDER_LEFT * SQUARE_SIZE, (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    mMinesLeftIndicator->setFont(mContext->assets.GetFont("default_font"));

    mTimeLeftIndicator = std::make_shared<Indicator>();
    mTimeLeftIndicator->setTexture(mContext->assets.GetTexture("led_background"));
    mTimeLeftIndicator->setTextureRect({0, 0, SQUARE_SIZE * 3, SQUARE_SIZE});
    mTimeLeftIndicator->setPosition((GAME_BORDER_LEFT + difficulty.field_width - 3) * SQUARE_SIZE,
                                    (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    mTimeLeftIndicator->setFont(mContext->assets.GetFont("default_font"));

    auto &fieldTexture = mContext->assets.GetTexture("tile_texture");
    fieldTexture.setRepeated(true);
    mGridSprite.setPosition(GAME_BORDER_LEFT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);
    mGridSprite.setTextureRect(TILE_INT_RECT(17));

    mSmileButton = std::make_shared<Button>();
    mSmileButton->setTexture(mContext->assets.GetTexture("smiles_button"));
    mSmileButton->setPosition(
            (GAME_BORDER_LEFT + difficulty.field_width / 2 - (difficulty.field_width % 2 ? 0 : 1)) * SQUARE_SIZE,
            (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    mSmileButton->setCallback([this]() {
        reset();
    });
    mIsSmileSmall = difficulty.field_width % 2 ? true : false;
    reset();

    mGuiContainer.pack(background);
    mGuiContainer.pack(mainMenuButton);
    mGuiContainer.pack(exitButton);
    mGuiContainer.pack(mMinesLeftIndicator);
    mGuiContainer.pack(mTimeLeftIndicator);
    mGuiContainer.pack(mSmileButton);
}

void GameState::HandleInput() {
    sf::Event event;

    while (mContext->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);

        auto fieldRect = sf::IntRect(GAME_BORDER_LEFT * SQUARE_SIZE,
                                     GAME_BORDER_TOP * SQUARE_SIZE,
                                     mContext->difficulty.field_width * SQUARE_SIZE,
                                     mContext->difficulty.field_height * SQUARE_SIZE);
        switch (event.type) {
            case sf::Event::Closed:
                mContext->window.close();
                break;
            case sf::Event::MouseMoved: {

            }
            case sf::Event::MouseButtonReleased: {
                auto mousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (mGameState == GameState::State::GamePlaying
                        || mGameState == GameState::State::GameFirstMove) {
                        if (fieldRect.contains(mousePos)) {
                            if (mGameState == GameState::State::GameFirstMove)
                                mGameClock.restart();

                            int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                            int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                            if (mGameState == GameState::State::GameFirstMove) {
                                mGameState = GameState::State::GamePlaying;
                                initGridArray(col, row);
                            }

                            revealCell(col, row);
                            mSmileReaction = GameState::SmileReaction::SmileUsual;
                            mNeedToUpdate = true;
                        }
                    }
                }
                if (mGameState == GameState::State::GamePlaying && event.mouseButton.button == sf::Mouse::Right) {
                    if (fieldRect.contains(mousePos)) {
                        int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                        int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                        if (mGameState == GameState::State::GamePlaying &&
                            mMinesCount > -5) {
                            markCell(col, row);
                            mNeedToUpdate = true;
                        }
                    }
                }
            }
            case sf::Event::MouseButtonPressed: {
                auto mousePos = sf::Mouse::getPosition(mContext->window);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // если игра - PLAYING, то находим нажатую ячейку
                    // делаем ячейчку выбранной
                    // а смайл улыбающимся
                    if (mGameState == GameState::State::GamePlaying) {
                        if (fieldRect.contains(mousePos)) {
                            int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                            int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                            mGridArray.at(row * mContext->difficulty.field_width + col) |= CELL_SELECTED;
                            mSmileReaction = GameState::SmileReaction::SmileReveal;
                            mNeedToUpdate = true;
                        }
                    }
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                    // если игра - PLAYING, то находим нажатую ячейку
                    // делаем ячейчки выбранными +1 -1 в разные стороный от выбранной мыши
                    if (fieldRect.contains(mousePos) && mGameState == GameState::State::GamePlaying) {
                        int col = ((mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE);
                        int row = ((mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE);

                        selectCellsArea(col, row);
                    }
                } else {
                    if (mGameState == GameState::State::GameLose) {
                        mSmileReaction = GameState::SmileReaction::SmileLose;
                    } else if (mGameState == GameState::State::GameWon) {
                        mSmileReaction = GameState::SmileReaction::SmileWin;
                    } else {
                        mSmileReaction = GameState::SmileReaction::SmileUsual;
                    }
                }
                mNeedToUpdate = true;
                break;
            }
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::R) {
                    reset();
                }
            }
        }
    }
}

void GameState::Update() {
    if (mNeedToUpdate) {
        if (mGameState == GameState::State::GamePlaying) {
            updateGridCells();
        }
        if (mGameState == GameState::State::GameLose) {
            updateGridCellsOnLose();
        }
        if (mGameState == GameState::State::GameWon) {
            updateGridCellsOnWin();
        }
        mNeedToUpdate = false;
    }

    if (mGameState == GameState::State::GamePlaying) {
        updateTimer();
        checkOnWin();
    }

    if (mIsSmileSmall)
        mSmileButton->setTextureRect(SMILE_SMALL_INT_RECT(mSmileReaction));
    else mSmileButton->setTextureRect(SMILE_LARGE_INT_RECT(mSmileReaction));
}

void GameState::reset() {
    mGameState = GameState::State::GameFirstMove;
    mMinesCount = mContext->difficulty.bomb_count;
    mNeedToUpdate = false;
    mGameTime = 0;
    mSmileReaction = GameState::SmileReaction::SmileUsual;

    mMinesLeftIndicator->setString(std::to_string(mMinesCount));
    mTimeLeftIndicator->setString(std::to_string(mGameTime));

    initGridCells();
}


void GameState::Draw() {
    mContext->window.clear(sf::Color::Red);

    mContext->window.draw(mGuiContainer);

    for (auto cell: mGridCells) {
        mContext->window.draw(cell);
    }

    mContext->window.display();
}

void GameState::initGridCells() {
    mGridCells.clear();
    auto difficulty = mContext->difficulty;

    int cellCount = difficulty.field_height * difficulty.field_width;
    for (int i = 0; i < cellCount; i++) {
        int cell_y = std::ceil(i / difficulty.field_width);
        int cell_x = i % difficulty.field_width;
        sf::Sprite cell;
        cell.setTexture(mContext->assets.GetTexture("tile_texture"));
        cell.setTextureRect(TILE_INT_RECT(11));
        auto position = sf::Vector2f((GAME_BORDER_LEFT + cell_x) * SQUARE_SIZE,
                                     (GAME_BORDER_TOP + cell_y) * SQUARE_SIZE);
        cell.setPosition(position);

        mGridCells.push_back(cell);
    }
}

void GameState::initGridArray(int x, int y) {
    mGridArray.clear();
    mCellsRevealed = 0;

    auto difficulty = mContext->difficulty;

    int cellCount = difficulty.field_height * difficulty.field_width;
    int firstMoveCell = y * difficulty.field_width + x;
    for (int i = 0; i < cellCount; i++) {
        mGridArray.push_back(0);
    }

    for (int i = 0; i < mContext->difficulty.bomb_count; i++) {
        int randCol = rand() % (difficulty.field_width);
        int randRow = rand() % (difficulty.field_height);
        int cellNum = randRow * difficulty.field_width + randCol;
        if (mGridArray.at(cellNum) == CELL_BOMB || cellNum == firstMoveCell) {
            i--;
            continue;
        }
        mGridArray.at(cellNum) = CELL_BOMB;
        for (int row = (randRow - 1); row <= randRow + 1; row++) {
            if (row >= 0 && row < difficulty.field_height) {
                for (int col = (randCol - 1); col <= randCol + 1; col++) {
                    if (col >= 0 && col < difficulty.field_width) {
                        if (mGridArray.at(row * difficulty.field_width + col) < CELL_BOMB)
                            mGridArray.at(row * difficulty.field_width + col)++;
                    }
                }
            }
        }
    }
}

void GameState::revealCell(int x, int y) {
    auto difficulty = mContext->difficulty;
    if (mGridArray.at(y * mContext->difficulty.field_width + x) & CELL_FLAG) {
        return;
    }
    if (mGridArray.at(y * mContext->difficulty.field_width + x) & CELL_REVEALED) {
        return;
    }
    if (mGridArray.at(y * mContext->difficulty.field_width + x) == CELL_BOMB) {
        mGameState = GameState::State::GameLose;
        mGridArray.at(y * mContext->difficulty.field_width + x) = CELL_BOMB_DETONATED;
        return;
    }

    mGridArray.at(y * mContext->difficulty.field_width + x) &= 0xF;
    mGridArray.at(y * mContext->difficulty.field_width + x) |= CELL_REVEALED;
    mCellsRevealed++;

    if ((mGridArray.at(y * difficulty.field_width + x) & 0xF) == CELL_EMPTY) {
        for (int row = (y - 1); row <= y + 1; row++) {
            if (row >= 0 && row < difficulty.field_height) {
                for (int col = (x - 1); col <= x + 1; col++) {
                    if (col >= 0 && col < difficulty.field_width) {
                        if (!(mGridArray.at(row * difficulty.field_width + col) & CELL_REVEALED)) {
                            if (row == y && col == x) continue;
                            revealCell(col, row);
                        }
                    }
                }
            }
        }
    }
}

void GameState::markCell(int x, int y) {
    if (mGridArray.at(y * mContext->difficulty.field_width + x) & CELL_REVEALED)
        return;

    if (mGridArray.at(y * mContext->difficulty.field_width + x) & CELL_FLAG) {
        mGridArray.at(y * mContext->difficulty.field_width + x) ^= CELL_FLAG;
        mGridArray.at(y * mContext->difficulty.field_width + x) ^= CELL_QUESTION;
        mMinesCount++;
        return;
    }

    if (!(mGridArray.at(y * mContext->difficulty.field_width + x) & CELL_FLAG) &&
        !(mGridArray.at(y * mContext->difficulty.field_width + x) & CELL_QUESTION)) {
        mGridArray.at(y * mContext->difficulty.field_width + x) |= CELL_FLAG;
        mMinesCount--;
        return;
    }

    if (mGridArray.at(y * mContext->difficulty.field_width + x) & CELL_QUESTION) {
        mGridArray.at(y * mContext->difficulty.field_width + x) ^= CELL_QUESTION;
    }
}

void GameState::updateGridCellsOnLose() {
    int fieldSize = mContext->difficulty.field_height * mContext->difficulty.field_width;
    for (int i = 0; i < fieldSize; i++) {
        if (mGridArray.at(i) & CELL_FLAG && ((mGridArray.at(i) & 0xF) != CELL_BOMB)) {
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(14));
        } else if (((mGridArray.at(i) & 0xF) == CELL_BOMB) && (mGridArray.at(i) & CELL_FLAG)) {
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(12));
            continue;
        } else if (mGridArray.at(i) == CELL_BOMB) {
            int cellValue = mGridArray.at(i) & 0xF;
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(cellValue));
        } else if (mGridArray.at(i) == CELL_BOMB_DETONATED) {
            int cellValue = mGridArray.at(i) & 0xF;
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(cellValue));
        }
    }
}

void GameState::updateGridCellsOnWin() {
    int fieldSize = mContext->difficulty.field_height * mContext->difficulty.field_width;
    for (int i = 0; i < fieldSize; i++) {
        if (mGridArray.at(i) == CELL_BOMB && (mGridArray.at(i) & CELL_FLAG)) {
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(12));
            continue;
        } else if (mGridArray.at(i) == CELL_BOMB) {
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(12));
        } else if (mGridArray.at(i) == CELL_BOMB_DETONATED) {
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(12));
        }
    }
    if (mContext->difficulty.difficulty_type != GAME_CUSTOM) {
        mContext->lastResults.time = mGameTime > 999 ? 999 : mGameTime;
        mContext->lastResults.name = "";
        mContext->lastResults.game_type = mContext->difficulty.difficulty_type;
        if (mContext->leaderboard.CheckResult(mContext->lastResults))
            mContext->manager.AddState(StateRef(new RecordSaveState(mContext)), true);
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

void GameState::checkOnWin() {
    auto difficulty = mContext->difficulty;
    int cellsLeft = difficulty.field_width * difficulty.field_height - mCellsRevealed;
    if (cellsLeft == difficulty.bomb_count) {
        mGameState = GameState::State::GameWon;
        mSmileReaction = GameState::SmileReaction::SmileWin;
    }
}

void GameState::updateGridCells() {
    int fieldSize = mContext->difficulty.field_height * mContext->difficulty.field_width;
    for (int i = 0; i < fieldSize; i++) {
        if (mGridArray.at(i) & CELL_REVEALED) {
            int cellValue = mGridArray.at(i) & 0xF;
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(cellValue));
        } else if (mGridArray.at(i) & CELL_FLAG) {
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(12));
        } else if (mGridArray.at(i) & CELL_QUESTION) {
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(13));
        } else if (mGridArray.at(i) & CELL_SELECTED) {
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(0));
            mGridArray.at(i) &= 0xF;
        } else {
            mGridCells.at(i).setTextureRect(TILE_INT_RECT(11));
        }
    }
    mMinesLeftIndicator->setString(std::to_string(mMinesCount));
}

void GameState::selectCellsArea(int col, int row) {
    auto difficulty = mContext->difficulty;

    for (int i = row ? row - 1 : row;
         i <= (row + 1 < difficulty.field_height ? row + 1 : difficulty.field_height - 1); i++) {
        for (int j = col ? col - 1 : col;
             j <= (col + 1 < difficulty.field_width ? col + 1 : difficulty.field_width - 1); j++) {
            int cell_num = i * mContext->difficulty.field_width + j;
            mGridArray.at(cell_num) |= CELL_SELECTED;
        }
    }
}
