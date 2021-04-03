#include "GameState.h"
#include "MainMenuState.h"
#include "../DEFINITIONS.h"

#include <iostream>
#include <sstream>

GameState::GameState(GameDataRef data) : _data(data) {

}

void GameState::Init() {
    auto difficulty = this->_data->difficulty;
    this->_data->window.create(sf::VideoMode((difficulty.field_width + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                             (difficulty.field_height + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                                                    "Minesweeper",
                                                    sf::Style::Titlebar | sf::Style::Close);
    auto& backgroundTexture = this->_data->assets.GetTexture("background");
    auto windowSize = this->_data->window.getSize();

    backgroundTexture.setRepeated(true);
    this->_background.setTexture(backgroundTexture);
    this->_background.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto& fieldTexture = this->_data->assets.GetTexture("tile_texture");
    fieldTexture.setRepeated(true);
    this->_gridSprite.setPosition(GAME_BORDER_LEFT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);
    this->_gridSprite.setTextureRect(TILE_INT_RECT(17));

    this->_mainMenuButton.setTexture(this->_data->assets.GetTexture("state_buttons"));
    this->_mainMenuButton.setTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    this->_mainMenuButton.setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);

    this->_exitButton.setTexture(this->_data->assets.GetTexture("state_buttons"));
    this->_exitButton.setTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    this->_exitButton.setPosition((difficulty.field_width + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);

    auto& ledBackground = this->_data->assets.GetTexture("led_background");
    ledBackground.setRepeated(true);
    this->_minesLeftSprite.setTexture(ledBackground);
    this->_minesLeftSprite.setTextureRect({0, 0, SQUARE_SIZE * 3, SQUARE_SIZE});
    this->_minesLeftSprite.setPosition(GAME_BORDER_LEFT * SQUARE_SIZE, (GAME_BORDER_TOP-2) * SQUARE_SIZE);

    this->_minesLeftText.setFont(this->_data->assets.GetFont("default_font"));
    this->_minesLeftText.setCharacterSize(20);
    this->_minesLeftText.setStyle(sf::Text::Bold);
    this->_minesLeftText.setScale(2.f, 2.f);
    this->_minesLeftText.setPosition(GAME_BORDER_LEFT * SQUARE_SIZE + 6, (GAME_BORDER_TOP-3) * SQUARE_SIZE + 18);

    this->_gameTimerSprite.setTexture(ledBackground);
    this->_gameTimerSprite.setTextureRect({0, 0, SQUARE_SIZE * 3, SQUARE_SIZE});
    this->_gameTimerSprite.setPosition((GAME_BORDER_LEFT + difficulty.field_width - 3) * SQUARE_SIZE, (GAME_BORDER_TOP-2) * SQUARE_SIZE);
    this->_gameTimerText.setFont(this->_data->assets.GetFont("default_font"));
    this->_gameTimerText.setCharacterSize(20);
    this->_gameTimerText.setStyle(sf::Text::Bold);
    this->_gameTimerText.setScale(2.f, 2.f);
    this->_gameTimerText.setPosition((GAME_BORDER_LEFT + difficulty.field_width - 3) * SQUARE_SIZE + 6, (GAME_BORDER_TOP-3) * SQUARE_SIZE + 18);

    auto& smileButtonTexture = this->_data->assets.GetTexture("smiles_button");
    this->_smileButton.setTexture(smileButtonTexture);
    this->_smileButton.setPosition((GAME_BORDER_LEFT + 4) * SQUARE_SIZE, (GAME_BORDER_TOP-2) * SQUARE_SIZE);
    this->_isSmileSmall = difficulty.field_width % 2 ? true : false;
    this->Reset();
}

void GameState::HandleInput()
{
    sf::Event event;

    while (this->_data->window.pollEvent(event))
    {

        auto fieldRect = sf::IntRect(GAME_BORDER_LEFT * SQUARE_SIZE,
                                     GAME_BORDER_TOP * SQUARE_SIZE,
                                     this->_data->difficulty.field_width * SQUARE_SIZE,
                                     this->_data->difficulty.field_height * SQUARE_SIZE);
        switch (event.type) {
            case sf::Event::Closed:
                this->_data->window.close();
                break;
            case sf::Event::MouseMoved: {
                auto mousePos = sf::Vector2f((float) event.mouseMove.x, (float) event.mouseMove.y);

                if (this->_mainMenuButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    this->_mainMenuButton.setTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
                else this->_mainMenuButton.setTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});

                if (this->_exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    this->_exitButton.setTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
                else this->_exitButton.setTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
            }
            case sf::Event::MouseButtonReleased: {
                auto mousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (this->_gameState == STATE_PLAYING || this->_gameState == STATE_FIRST_MOVE) {
                        if (fieldRect.contains(mousePos)) {
                            if (this->_gameState == STATE_FIRST_MOVE)
                                this->_gameClock.restart();

                            int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                            int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                            if (this->_gameState == STATE_FIRST_MOVE) {
                                this->_gameState = STATE_PLAYING;
                                InitGridArray(col, row);
                            }

                            this->RevealCell(col, row);
                            this->_smileReaction = SMILE_USUAL;
                            _isUpdate = true;
                        }
                    }
                }
                if (this->_gameState == STATE_PLAYING && event.mouseButton.button == sf::Mouse::Right) {
                    if (fieldRect.contains(mousePos)) {
                        int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                        int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                        if (this->_gameState == STATE_PLAYING &&
                            this->_minesCount > -5) {
                            this->MarkCell(col, row);
                            _isUpdate = true;
                        }
                    }
                }
                if (this->_smileButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    this->Reset();
                }
            }
            case sf::Event::MouseButtonPressed: {
                auto mousePos = sf::Mouse::getPosition(this->_data->window);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (this->_gameState == STATE_PLAYING) {
                        if (fieldRect.contains(mousePos)) {
                            int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                            int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                            this->_gridArray.at(row * this->_data->difficulty.field_width + col) |= CELL_SELECTED;
                            this->_smileReaction = SMILE_REVEAL;
                            _isUpdate = true;
                        }
                    }
                    if (this->_exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                        this->_data->window.close();
                    }
                    if (this->_mainMenuButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                        this->_data->manager.AddState(StateRef(new MainMenuState(this->_data)), true);
                    }
                    if (this->_smileButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                        this->_smileReaction = SMILE_CLICK;
                    }
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                    if (fieldRect.contains(mousePos) && this->_gameState == STATE_PLAYING) {
                        int col = ((mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE);
                        int row = ((mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE);
                        auto difficulty = this->_data->difficulty;

                        for (int i = row ? row-1 : row; i <= (row+1<difficulty.field_height? row+1 : difficulty.field_height-1); i++) {
                            for (int j = col ? col - 1 : col;
                                 j <= (col + 1 < difficulty.field_width ? col + 1 : difficulty.field_width - 1); j++) {
                                int cell_num = i * this->_data->difficulty.field_width + j;
                                this->_gridArray.at(cell_num) |= CELL_SELECTED;
                            }
                        }
                    }
                } else {
                    if (this->_gameState == STATE_LOSE) {
                        this->_smileReaction = SMILE_LOSE;
                    } else if (this->_gameState == STATE_WON) {
                        this->_smileReaction = SMILE_WIN;
                    } else {
                        this->_smileReaction = SMILE_USUAL;
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
        if (this->_gameState == STATE_PLAYING) {
            int fieldSize = this->_data->difficulty.field_height * this->_data->difficulty.field_width;
            for (int i = 0; i < fieldSize; i++) {
                if (this->_gridArray.at(i) & CELL_REVEALED) {
                    int cellValue = this->_gridArray.at(i) & 0xF;
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(cellValue));
                } else if (this->_gridArray.at(i) & CELL_FLAG) {
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(12));
                } else if (this->_gridArray.at(i) & CELL_QUESTION) {
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(13));
                } else if (this->_gridArray.at(i) & CELL_SELECTED) {
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(0));
                    this->_gridArray.at(i) &= 0xF;
                }
                else {
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(11));
                }
            }
            std::ostringstream minesLeft;
            minesLeft << _minesCount;
            this->_minesLeftText.setString(minesLeft.str());
        }
        if (this->_gameState == STATE_LOSE) {
            int fieldSize = this->_data->difficulty.field_height * this->_data->difficulty.field_width;
            for (int i = 0; i < fieldSize; i++) {
                if (this->_gridArray.at(i) & CELL_FLAG && this->_gridArray.at(i) != CELL_BOMB) {
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(14));
                } else if (this->_gridArray.at(i) == CELL_BOMB && (this->_gridArray.at(i) & CELL_FLAG)) {
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(12));
                    continue;
                } else if (this->_gridArray.at(i) == CELL_BOMB) {
                    int cellValue = this->_gridArray.at(i) & 0xF;
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(cellValue));
                } else if (this->_gridArray.at(i) == CELL_BOMB_DETONATED) {
                    int cellValue = this->_gridArray.at(i) & 0xF;
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(cellValue));
                }
            }
        }
        if (this->_gameState == STATE_WON) {
            int fieldSize = this->_data->difficulty.field_height * this->_data->difficulty.field_width;
            for (int i = 0; i < fieldSize; i++) {
                if (this->_gridArray.at(i) == CELL_BOMB && (this->_gridArray.at(i) & CELL_FLAG)) {
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(12));
                    continue;
                } else if (this->_gridArray.at(i) == CELL_BOMB) {
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(12));
                } else if (this->_gridArray.at(i) == CELL_BOMB_DETONATED) {
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(12));
                }
            }
        }
        _isUpdate = false;
    }

    if (this->_gameState == STATE_PLAYING) {
        this->_gameTimer = this->_gameClock.getElapsedTime();
        if (this->_gameTimer.asSeconds() > this->_gameTime) {
            if (this->_gameTime < 999) {
                this->_gameTime++;
                std::ostringstream gameTimer;
                gameTimer << this->_gameTime;
                this->_gameTimerText.setString(gameTimer.str());
            }
        }

        auto difficulty = this->_data->difficulty;
        int cellsLeft = difficulty.field_width * difficulty.field_height - this->_cellsRevealed;
        if (cellsLeft == difficulty.bomb_count) {
            this->_gameState = STATE_WON;
            this->_smileReaction = SMILE_WIN;
        }
    }

    this->_smileButton.setTextureRect(SMILE_SMALL_INT_RECT(this->_smileReaction));
}

void GameState::Reset() {
    this->_gameState = STATE_FIRST_MOVE;
    this->_minesCount = this->_data->difficulty.bomb_count;
    this->_isUpdate = false;
    this->_gameTime = 0;
    this->_smileReaction = SMILE_USUAL;

    std::ostringstream minesLeft, gameTime;
    minesLeft << this->_minesCount;
    gameTime << this->_gameTime;

    this->_minesLeftText.setString(minesLeft.str());
    this->_gameTimerText.setString(gameTime.str());

    InitGridCells();
}


void GameState::Draw()
{
    this->_data->window.clear(sf::Color::Red);
    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_mainMenuButton);
    this->_data->window.draw(this->_exitButton);
    this->_data->window.draw(this->_minesLeftSprite);
    this->_data->window.draw(this->_minesLeftText);
    this->_data->window.draw(this->_gameTimerSprite);
    this->_data->window.draw(this->_gameTimerText);
    this->_data->window.draw(this->_smileButton);



    for (auto cell : this->_gridCells) {
        this->_data->window.draw(cell);
    }

    this->_data->window.display();
}

void GameState::InitGridCells() {
    this->_gridCells.clear();
    auto difficulty = this->_data->difficulty;

    int cellCount = difficulty.field_height * difficulty.field_width;
    for (int i = 0; i < cellCount; i++) {
        int cell_y = std::ceil(i / difficulty.field_width);
        int cell_x = i % difficulty.field_width;
        sf::Sprite cell;
        cell.setTexture(this->_data->assets.GetTexture("tile_texture"));
        cell.setTextureRect(TILE_INT_RECT(11));
        auto position = sf::Vector2f((GAME_BORDER_LEFT + cell_x) * SQUARE_SIZE,
                                     (GAME_BORDER_TOP + cell_y) * SQUARE_SIZE);
        cell.setPosition(position);

        this->_gridCells.push_back(cell);
    }
}

void GameState::InitGridArray(int x, int y) {
    this->_gridArray.clear();
    this->_cellsRevealed = 0;

    auto difficulty = this->_data->difficulty;

    int cellCount = difficulty.field_height * difficulty.field_width;
    int firstMoveCell = y * difficulty.field_width + x;
    for (int i = 0; i < cellCount; i++) {
        this->_gridArray.push_back(0);
    }

    for (int i = 0; i < this->_data->difficulty.bomb_count; i++) {
        int randCol = rand() % (difficulty.field_width - 1);
        int randRow = rand() % (difficulty.field_height - 1);
        int cellNum = randRow * difficulty.field_width + randCol;
        if (this->_gridArray.at(cellNum) == CELL_BOMB || cellNum == firstMoveCell) {
            i--;
            continue;
        }
        this->_gridArray.at(cellNum) = CELL_BOMB;
        for (int row = (randRow - 1); row <= randRow+1; row++) {
            if (row >= 0 && row < difficulty.field_height) {
                for (int col = (randCol - 1); col <= randCol+1; col++) {
                    if (col >= 0 && col < difficulty.field_width) {
                        if (this->_gridArray.at(row * difficulty.field_width + col) < CELL_BOMB)
                            _gridArray.at(row * difficulty.field_width + col)++;
                    }
                }
            }
        }
    }
}

void GameState::RevealCell(int x, int y) {
    auto difficulty = this->_data->difficulty;
    if (_gridArray.at(y * this->_data->difficulty.field_width + x) & CELL_FLAG) {
        return;
    }
    if (_gridArray.at(y * this->_data->difficulty.field_width + x) & CELL_REVEALED) {
        return;
    }
    if (_gridArray.at(y * this->_data->difficulty.field_width + x) == CELL_BOMB) {
        this->_gameState = STATE_LOSE;
        _gridArray.at(y * this->_data->difficulty.field_width + x) = CELL_BOMB_DETONATED;
        return;
    }

    _gridArray.at(y * this->_data->difficulty.field_width + x) &= 0xF;
    _gridArray.at(y * this->_data->difficulty.field_width + x) |= CELL_REVEALED;
    this->_cellsRevealed++;

    if ((this->_gridArray.at(y * difficulty.field_width + x) & 0xF) == CELL_EMPTY) {
        for (int row = (y - 1); row <= y + 1; row++) {
            if (row >= 0 && row < difficulty.field_height) {
                for (int col = (x - 1); col <= x + 1; col++) {
                    if (col >= 0 && col < difficulty.field_width) {
                        if (!(this->_gridArray.at(row * difficulty.field_width + col) & CELL_REVEALED)) {
                            if (row == y && col == x) continue;
                            this->RevealCell(col, row);
                       }
                    }
                }
            }
        }
    }
}

void GameState::MarkCell(int x, int y) {
    if (this->_gridArray.at(y * this->_data->difficulty.field_width + x) & CELL_REVEALED)
        return;

    if (this->_gridArray.at(y * this->_data->difficulty.field_width + x) & CELL_FLAG) {
        this->_gridArray.at(y * this->_data->difficulty.field_width + x) ^= CELL_FLAG;
        this->_gridArray.at(y * this->_data->difficulty.field_width + x) ^= CELL_QUESTION;
        this->_minesCount++;
        return;
    }

    if (!(this->_gridArray.at(y * this->_data->difficulty.field_width + x) & CELL_FLAG) &&
        !(this->_gridArray.at(y * this->_data->difficulty.field_width + x) & CELL_QUESTION)) {
        this->_gridArray.at(y * this->_data->difficulty.field_width + x) |= CELL_FLAG;
        this->_minesCount--;
        return;
    }

    if (this->_gridArray.at(y * this->_data->difficulty.field_width + x) & CELL_QUESTION) {
        this->_gridArray.at(y * this->_data->difficulty.field_width + x) ^= CELL_QUESTION;
    }
}
