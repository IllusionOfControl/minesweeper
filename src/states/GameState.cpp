#include "GameState.h"
#include "MainMenuState.h"
#include "../DEFINITIONS.h"
#include "../gui/Background.hpp"
#include "../gui/Button.hpp"


#include <iostream>
#include <sstream>

GameState::GameState(GameDataRef data)
        : _data(data)
        , mGuiContainer() {

}

void GameState::Init() {
    auto difficulty = _data->difficulty;
    _data->window.create(
            sf::VideoMode((difficulty.field_width + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                          (difficulty.field_height + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
            "Minesweeper",
            sf::Style::Titlebar | sf::Style::Close);
    auto windowSize = _data->window.getSize();

    auto background = std::make_shared<Background>();
    background->setTexture(_data->assets.GetTexture("background"));
    background->setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto mainMenuButton = std::make_shared<Button>();
    mainMenuButton->setTexture(_data->assets.GetTexture("state_buttons"));
    mainMenuButton->setNormalTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setSelectedTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);
    mainMenuButton->setCallback([&]() {
        _data->manager.AddState(StateRef(new MainMenuState(_data)), true);
    });

    auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(_data->assets.GetTexture("state_buttons"));
    exitButton->setNormalTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setSelectedTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setPosition((difficulty.field_width + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);
    exitButton->setCallback([&]() {
        _data->window.close();
    });

    mMinesLeftIndicator = std::make_shared<Indicator>();
    mMinesLeftIndicator->setTexture(_data->assets.GetTexture("led_background"));
    mMinesLeftIndicator->setTextureRect({0, 0, SQUARE_SIZE * 3, SQUARE_SIZE});
    mMinesLeftIndicator->setPosition(GAME_BORDER_LEFT * SQUARE_SIZE, (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    mMinesLeftIndicator->setFont(_data->assets.GetFont("default_font"));

    mTimeLeftIndicator = std::make_shared<Indicator>();
    mTimeLeftIndicator->setTexture(_data->assets.GetTexture("led_background"));
    mTimeLeftIndicator->setTextureRect({0, 0, SQUARE_SIZE * 3, SQUARE_SIZE});
    mTimeLeftIndicator->setPosition((GAME_BORDER_LEFT + difficulty.field_width - 3) * SQUARE_SIZE,
                                    (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    mTimeLeftIndicator->setFont(_data->assets.GetFont("default_font"));

    auto &fieldTexture = _data->assets.GetTexture("tile_texture");
    fieldTexture.setRepeated(true);
    _gridSprite.setPosition(GAME_BORDER_LEFT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);
    _gridSprite.setTextureRect(TILE_INT_RECT(17));

    auto &smileButtonTexture = _data->assets.GetTexture("smiles_button");
    _smileButton.setTexture(smileButtonTexture);
    _smileButton.setPosition(
            (GAME_BORDER_LEFT + difficulty.field_width / 2 - (difficulty.field_width % 2 ? 0 : 1)) * SQUARE_SIZE,
            (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    _isSmileSmall = difficulty.field_width % 2 ? true : false;
    Reset();

    mGuiContainer.pack(background);
    mGuiContainer.pack(mainMenuButton);
    mGuiContainer.pack(exitButton);
    mGuiContainer.pack(mMinesLeftIndicator);
    mGuiContainer.pack(mTimeLeftIndicator);
}

void GameState::HandleInput() {
    sf::Event event;

    while (_data->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);

        auto fieldRect = sf::IntRect(GAME_BORDER_LEFT * SQUARE_SIZE,
                                     GAME_BORDER_TOP * SQUARE_SIZE,
                                     _data->difficulty.field_width * SQUARE_SIZE,
                                     _data->difficulty.field_height * SQUARE_SIZE);
        switch (event.type) {
            case sf::Event::Closed:
                _data->window.close();
                break;
            case sf::Event::MouseMoved: {

            }
            case sf::Event::MouseButtonReleased: {
                auto mousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (_gameState == STATE_PLAYING || _gameState == STATE_FIRST_MOVE) {
                        if (fieldRect.contains(mousePos)) {
                            if (_gameState == STATE_FIRST_MOVE)
                                _gameClock.restart();

                            int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                            int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                            if (_gameState == STATE_FIRST_MOVE) {
                                _gameState = STATE_PLAYING;
                                InitGridArray(col, row);
                            }

                            RevealCell(col, row);
                            _smileReaction = SMILE_USUAL;
                            _isUpdate = true;
                        }
                    }
                }
                if (_gameState == STATE_PLAYING && event.mouseButton.button == sf::Mouse::Right) {
                    if (fieldRect.contains(mousePos)) {
                        int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                        int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                        if (_gameState == STATE_PLAYING &&
                            _minesCount > -5) {
                            MarkCell(col, row);
                            _isUpdate = true;
                        }
                    }
                }
                if (_smileButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    Reset();
                }
            }
            case sf::Event::MouseButtonPressed: {
                auto mousePos = sf::Mouse::getPosition(_data->window);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // если игра - PLAYING, то находим нажатую ячейку
                    // делаем ячейчку выбранной
                    // а смайл улыбающимся
                    if (_gameState == STATE_PLAYING) {
                        if (fieldRect.contains(mousePos)) {
                            int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                            int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                            _gridArray.at(row * _data->difficulty.field_width + col) |= CELL_SELECTED;
                            _smileReaction = SMILE_REVEAL;
                            _isUpdate = true;
                        }
                    }
                    if (_exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                        _data->window.close();
                    }
                    if (_mainMenuButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                        _data->manager.AddState(StateRef(new MainMenuState(_data)), true);
                    }
                    if (_smileButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                        _smileReaction = SMILE_CLICK;
                    }
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                    // если игра - PLAYING, то находим нажатую ячейку
                    // делаем ячейчки выбранными +1 -1 в разные стороный от выбранной мыши
                    if (fieldRect.contains(mousePos) && _gameState == STATE_PLAYING) {
                        int col = ((mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE);
                        int row = ((mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE);
                        auto difficulty = _data->difficulty;

                        for (int i = row ? row - 1 : row;
                             i <= (row + 1 < difficulty.field_height ? row + 1 : difficulty.field_height - 1); i++) {
                            for (int j = col ? col - 1 : col;
                                 j <= (col + 1 < difficulty.field_width ? col + 1 : difficulty.field_width - 1); j++) {
                                int cell_num = i * _data->difficulty.field_width + j;
                                _gridArray.at(cell_num) |= CELL_SELECTED;
                            }
                        }
                    }
                } else {
                    if (_gameState == STATE_LOSE) {
                        _smileReaction = SMILE_LOSE;
                    } else if (_gameState == STATE_WON) {
                        _smileReaction = SMILE_WIN;
                    } else {
                        _smileReaction = SMILE_USUAL;
                    }
                }
                _isUpdate = true;
                break;
            }
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::R) {
                    Reset();
                }
            }
        }
    }
}

void GameState::Update() {
    if (_isUpdate) {
        if (_gameState == STATE_PLAYING) {
            int fieldSize = _data->difficulty.field_height * _data->difficulty.field_width;
            for (int i = 0; i < fieldSize; i++) {
                if (_gridArray.at(i) & CELL_REVEALED) {
                    int cellValue = _gridArray.at(i) & 0xF;
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(cellValue));
                } else if (_gridArray.at(i) & CELL_FLAG) {
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(12));
                } else if (_gridArray.at(i) & CELL_QUESTION) {
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(13));
                } else if (_gridArray.at(i) & CELL_SELECTED) {
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(0));
                    _gridArray.at(i) &= 0xF;
                } else {
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(11));
                }
            }
            std::ostringstream minesLeft;
            minesLeft << _minesCount;
            mMinesLeftIndicator->setString(minesLeft.str());
        }
        if (_gameState == STATE_LOSE) {
            int fieldSize = _data->difficulty.field_height * _data->difficulty.field_width;
            for (int i = 0; i < fieldSize; i++) {
                if (_gridArray.at(i) & CELL_FLAG && ((_gridArray.at(i) & 0xF) != CELL_BOMB)) {
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(14));
                } else if (((_gridArray.at(i) & 0xF) == CELL_BOMB) && (_gridArray.at(i) & CELL_FLAG)) {
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(12));
                    continue;
                } else if (_gridArray.at(i) == CELL_BOMB) {
                    int cellValue = _gridArray.at(i) & 0xF;
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(cellValue));
                } else if (_gridArray.at(i) == CELL_BOMB_DETONATED) {
                    int cellValue = _gridArray.at(i) & 0xF;
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(cellValue));
                }
            }
        }
        if (_gameState == STATE_WON) {
            int fieldSize = _data->difficulty.field_height * _data->difficulty.field_width;
            for (int i = 0; i < fieldSize; i++) {
                if (_gridArray.at(i) == CELL_BOMB && (_gridArray.at(i) & CELL_FLAG)) {
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(12));
                    continue;
                } else if (_gridArray.at(i) == CELL_BOMB) {
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(12));
                } else if (_gridArray.at(i) == CELL_BOMB_DETONATED) {
                    _gridCells.at(i).setTextureRect(TILE_INT_RECT(12));
                }
            }
            if (_data->difficulty.difficulty_type != GAME_CUSTOM) {
                _data->lastResults.time = _gameTime > 999 ? 999 : _gameTime;
                _data->lastResults.name = "";
                _data->lastResults.game_type = _data->difficulty.difficulty_type;
                if (_data->leaderboard.CheckResult(_data->lastResults))
                    _data->manager.AddState(StateRef(new RecordSaveState(_data)), true);
            }
        }
        _isUpdate = false;
    }

    if (_gameState == STATE_PLAYING) {
        _gameTimer = _gameClock.getElapsedTime();
        if (_gameTimer.asSeconds() > _gameTime) {
            if (_gameTime < 999) {
                _gameTime++;
                std::ostringstream gameTimer;
                gameTimer << _gameTime;
                mTimeLeftIndicator->setString(gameTimer.str());
            }
        }

        auto difficulty = _data->difficulty;
        int cellsLeft = difficulty.field_width * difficulty.field_height - _cellsRevealed;
        if (cellsLeft == difficulty.bomb_count) {
            _gameState = STATE_WON;
            _smileReaction = SMILE_WIN;
        }
    }

    if (_isSmileSmall)
        _smileButton.setTextureRect(SMILE_SMALL_INT_RECT(_smileReaction));
    else _smileButton.setTextureRect(SMILE_LARGE_INT_RECT(_smileReaction));
}

void GameState::Reset() {
    _gameState = STATE_FIRST_MOVE;
    _minesCount = _data->difficulty.bomb_count;
    _isUpdate = false;
    _gameTime = 0;
    _smileReaction = SMILE_USUAL;

    std::ostringstream minesLeft, gameTime;
    minesLeft << _minesCount;
    gameTime << _gameTime;

    mMinesLeftIndicator->setString(minesLeft.str());
    mTimeLeftIndicator->setString(gameTime.str());

    InitGridCells();
}


void GameState::Draw() {
    _data->window.clear(sf::Color::Red);

    _data->window.draw(mGuiContainer);
    _data->window.draw(_smileButton);

    for (auto cell: _gridCells) {
        _data->window.draw(cell);
    }

    _data->window.display();
}

void GameState::InitGridCells() {
    _gridCells.clear();
    auto difficulty = _data->difficulty;

    int cellCount = difficulty.field_height * difficulty.field_width;
    for (int i = 0; i < cellCount; i++) {
        int cell_y = std::ceil(i / difficulty.field_width);
        int cell_x = i % difficulty.field_width;
        sf::Sprite cell;
        cell.setTexture(_data->assets.GetTexture("tile_texture"));
        cell.setTextureRect(TILE_INT_RECT(11));
        auto position = sf::Vector2f((GAME_BORDER_LEFT + cell_x) * SQUARE_SIZE,
                                     (GAME_BORDER_TOP + cell_y) * SQUARE_SIZE);
        cell.setPosition(position);

        _gridCells.push_back(cell);
    }
}

void GameState::InitGridArray(int x, int y) {
    _gridArray.clear();
    _cellsRevealed = 0;

    auto difficulty = _data->difficulty;

    int cellCount = difficulty.field_height * difficulty.field_width;
    int firstMoveCell = y * difficulty.field_width + x;
    for (int i = 0; i < cellCount; i++) {
        _gridArray.push_back(0);
    }

    for (int i = 0; i < _data->difficulty.bomb_count; i++) {
        int randCol = rand() % (difficulty.field_width);
        int randRow = rand() % (difficulty.field_height);
        int cellNum = randRow * difficulty.field_width + randCol;
        if (_gridArray.at(cellNum) == CELL_BOMB || cellNum == firstMoveCell) {
            i--;
            continue;
        }
        _gridArray.at(cellNum) = CELL_BOMB;
        for (int row = (randRow - 1); row <= randRow + 1; row++) {
            if (row >= 0 && row < difficulty.field_height) {
                for (int col = (randCol - 1); col <= randCol + 1; col++) {
                    if (col >= 0 && col < difficulty.field_width) {
                        if (_gridArray.at(row * difficulty.field_width + col) < CELL_BOMB)
                            _gridArray.at(row * difficulty.field_width + col)++;
                    }
                }
            }
        }
    }
}

void GameState::RevealCell(int x, int y) {
    auto difficulty = _data->difficulty;
    if (_gridArray.at(y * _data->difficulty.field_width + x) & CELL_FLAG) {
        return;
    }
    if (_gridArray.at(y * _data->difficulty.field_width + x) & CELL_REVEALED) {
        return;
    }
    if (_gridArray.at(y * _data->difficulty.field_width + x) == CELL_BOMB) {
        _gameState = STATE_LOSE;
        _gridArray.at(y * _data->difficulty.field_width + x) = CELL_BOMB_DETONATED;
        return;
    }

    _gridArray.at(y * _data->difficulty.field_width + x) &= 0xF;
    _gridArray.at(y * _data->difficulty.field_width + x) |= CELL_REVEALED;
    _cellsRevealed++;

    if ((_gridArray.at(y * difficulty.field_width + x) & 0xF) == CELL_EMPTY) {
        for (int row = (y - 1); row <= y + 1; row++) {
            if (row >= 0 && row < difficulty.field_height) {
                for (int col = (x - 1); col <= x + 1; col++) {
                    if (col >= 0 && col < difficulty.field_width) {
                        if (!(_gridArray.at(row * difficulty.field_width + col) & CELL_REVEALED)) {
                            if (row == y && col == x) continue;
                            RevealCell(col, row);
                        }
                    }
                }
            }
        }
    }
}

void GameState::MarkCell(int x, int y) {
    if (_gridArray.at(y * _data->difficulty.field_width + x) & CELL_REVEALED)
        return;

    if (_gridArray.at(y * _data->difficulty.field_width + x) & CELL_FLAG) {
        _gridArray.at(y * _data->difficulty.field_width + x) ^= CELL_FLAG;
        _gridArray.at(y * _data->difficulty.field_width + x) ^= CELL_QUESTION;
        _minesCount++;
        return;
    }

    if (!(_gridArray.at(y * _data->difficulty.field_width + x) & CELL_FLAG) &&
        !(_gridArray.at(y * _data->difficulty.field_width + x) & CELL_QUESTION)) {
        _gridArray.at(y * _data->difficulty.field_width + x) |= CELL_FLAG;
        _minesCount--;
        return;
    }

    if (_gridArray.at(y * _data->difficulty.field_width + x) & CELL_QUESTION) {
        _gridArray.at(y * _data->difficulty.field_width + x) ^= CELL_QUESTION;
    }
}
