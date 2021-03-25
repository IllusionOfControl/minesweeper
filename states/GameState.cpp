#include "GameState.h"
#include "MainMenuState.h"
#include "../DEFINITIONS.h"

#include <iostream>

GameState::GameState(GameDataRef data) : _data(data) {

}

void GameState::Init() {
    auto difficulty = this->_data->difficulty;
    this->_data->window.create(sf::VideoMode((difficulty.field_width + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                             (difficulty.field_height + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                               "Minesweeper");
    auto& backgroundTexture = this->_data->assets.GetTexture("background");
    auto windowSize = this->_data->window.getSize();

    backgroundTexture.setRepeated(true);
    this->_background.setTexture(backgroundTexture);
    this->_background.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto fieldSize = sf::IntRect(0, 0, this->_data->difficulty.field_width, this->_data->difficulty.field_height);
    auto& fieldTexture = this->_data->assets.GetTexture("tile_texture");
    fieldTexture.setRepeated(true);
    this->_gridSprite.setPosition(GAME_BORDER_LEFT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);
    this->_gridSprite.setTextureRect(TILE_INT_RECT(17));

    this->_gameState = STATE_FIRST_MOVE;
    this->_minesCount = difficulty.bomb_count;
    this->_isUpdate = false;
    InitGridCells();
}

void GameState::HandleInput()
{
    sf::Event event;

    while (this->_data->window.pollEvent(event))
    {
        auto mousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
        auto fieldRect = sf::IntRect(GAME_BORDER_LEFT * SQUARE_SIZE,
                                     GAME_BORDER_TOP * SQUARE_SIZE,
                                     this->_data->difficulty.field_width * SQUARE_SIZE,
                                     this->_data->difficulty.field_height * SQUARE_SIZE);
        switch (event.type) {
            case sf::Event::Closed:
                this->_data->window.close();
                break;
            case sf::Event::MouseMoved:
                break;
            case sf::Event::MouseButtonReleased:
                break;
            case sf::Event::MouseButtonPressed: {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (fieldRect.contains(mousePos)) {
                        int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                        int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                        if (this->_gameState == STATE_FIRST_MOVE) {
                            this->_gameState = STATE_PLAYING;
                            InitGridArray(col, row);
                        }

                        this->RevealCell(col, row);
                        _isUpdate = true;
                    }
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    if (fieldRect.contains(mousePos)) {
                        int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE) / SQUARE_SIZE;
                        int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE) / SQUARE_SIZE;

                        if (this->_gameState == STATE_PLAYING) {
                            this->MarkCell(col, row);
                            _isUpdate = true;
                        }
                    }
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
                } else {
                    this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(11));
                }
            }
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
        std::cout << this->_minesCount << std::endl;
    }
    _isUpdate = false;
}



void GameState::Draw()
{
    this->_data->window.clear(sf::Color::Red);
    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_pauseButton);
    for (auto cell : this->_gridCells) {
        this->_data->window.draw(cell);
    }

    this->_data->window.display();
}

void GameState::InitGridCells() {
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

    for (int i = 0; i < this->_data->difficulty.field_height; i++) {
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
    if (_gridArray.at(y * this->_data->difficulty.field_width + x) == CELL_BOMB) {
        this->_gameState = STATE_LOSE;
        _gridArray.at(y * this->_data->difficulty.field_width + x) = CELL_BOMB_DETONATED;
        return;
    }

    _gridArray.at(y * this->_data->difficulty.field_width + x) &= 0xF;
    _gridArray.at(y * this->_data->difficulty.field_width + x) |= CELL_REVEALED;


    if ((this->_gridArray.at(y * difficulty.field_width + x) & 0xF) == CELL_EMPTY) {
        for (int row = (y - 1); row <= y + 1; row++) {
            if (row >= 0 && row < difficulty.field_height) {
                for (int col = (x - 1); col <= x + 1; col++) {
                    if (col >= 0 && col < difficulty.field_width) {
                        if ((this->_gridArray.at(row * difficulty.field_width + col) & CELL_REVEALED) == 0) {
                            if (row == y && col == x) continue;
                            this->_cellsRevealed++;
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
