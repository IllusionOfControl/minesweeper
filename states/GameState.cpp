#include "GameState.h"

#include <sstream>
#include "GameState.h"
#include "MainMenuState.h"
#include "../DEFINITIONS.h"
//#include "GameOverState.hpp"

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

//    this->_gridSprite.setPosition(sf::Vector2f(GAME_BORDER_LEFT, GAME_BORDER_TOP));

//    _pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
//    _gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

    //InitGridPieces();
    InitGridArray(0);
    InitGridCells();
}

void GameState::HandleInput()
{
    sf::Event event;

    while (this->_data->window.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed:
                this->_data->window.close();
                break;
            case sf::Event::MouseMoved:
                break;
            case sf::Event::MouseButtonReleased:
                break;
            case sf::Event::MouseButtonPressed: {
                auto mousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                auto fieldRect = sf::IntRect(GAME_BORDER_LEFT * SQUARE_SIZE,
                                         GAME_BORDER_TOP * SQUARE_SIZE,
                                         this->_data->difficulty.field_width * SQUARE_SIZE,
                                         this->_data->difficulty.field_height * SQUARE_SIZE);
                if(fieldRect.contains(mousePos)) {
                    int col = (mousePos.x - GAME_BORDER_LEFT * SQUARE_SIZE)  / SQUARE_SIZE;
                    int row = (mousePos.y - GAME_BORDER_TOP * SQUARE_SIZE)  / SQUARE_SIZE;

                    RevealCell(col, row);
                    isMoved = true;
//                    int value = this->_gridArray.at(row * this->_data->difficulty.field_height + col);
//                    this->_gridCells.at(row * this->_data->difficulty.field_height + col).setTextureRect(TILE_INT_RECT(value));
//                    std::cout << value << std::endl;
                }
                break;
            }
        }

//        if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
//        {
//            // Switch To Game State
//            //this->_data->manager.AddState(StateRef(new PauseState(_data)), false);
//        }
//        else if (this->_data->input.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
//        {
//            if (STATE_PLAYING == gameState)
//            {
//                this->CheckAndPlacePiece();
//            }
//        }
    }
}

void GameState::Update() {
    if (isMoved) {
        int fieldSize = this->_data->difficulty.field_height * this->_data->difficulty.field_width;
        for (int i = 0; i < fieldSize; i++) {
            if (this->_gridArray.at(i) & CELL_REVEALED) {
                int cellValue = this->_gridArray.at(i) & 0xF;
                this->_gridCells.at(i).setTextureRect(TILE_INT_RECT(cellValue));
            }
        }
        isMoved = false;
    }
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

    for (int i = 0; i < this->_gridArray.size(); i++) {
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

void GameState::InitGridArray(int firstMove) {
    this->_gridArray.clear();
    this->cellsRevealed = 0;

    auto difficulty = this->_data->difficulty;

    int cellCount = this->_data->difficulty.field_height * this->_data->difficulty.field_width;
    for (int i = 0; i < cellCount; i++) {
        this->_gridArray.push_back(0);
    }

    for (int i = 0; i < this->_data->difficulty.field_height; i++) {
        int randCol = rand() % (difficulty.field_width - 1);
        int randRow = rand() % (difficulty.field_height - 1);
        int cellNum = randRow * difficulty.field_width + randCol;
        if (this->_gridArray.at(cellNum) == CELL_BOMB || cellNum == firstMove) {
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
    _gridArray.at(y * this->_data->difficulty.field_width + x) |= CELL_REVEALED;

    if ((this->_gridArray.at(y * difficulty.field_width + x) & 0xF) == CELL_EMPTY) {
        for (int row = (y - 1); row <= y + 1; row++) {
            if (row >= 0 && row < difficulty.field_height) {
                for (int col = (x - 1); col <= x + 1; col++) {
                    if (col >= 0 && col < difficulty.field_width) {
                        if ((this->_gridArray.at(row * difficulty.field_width + col) & CELL_REVEALED) == 0) {
                            if (row == y && col == x) continue;
                            this->cellsRevealed++;
                            this->RevealCell(col, row);
                       }
                    }
                }
            }
        }
    }
}


void GameState::CheckAndPlacePiece() {
    sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
    sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
    sf::Vector2f gapOutsideOfGrid = sf::Vector2f(0,0);

    sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

    //std::cout << gridLocalTouchPos.x << ", " << gridLocalTouchPos.y << std::endl;

    sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

    int column, row;

    // Check which column the user has clicked
    if (gridLocalTouchPos.x < gridSectionSize.x) // First Column
    {
        column = 1;
    }
    else if (gridLocalTouchPos.x < gridSectionSize.x * 2) // Second Column
    {
        column = 2;
    }
    else if (gridLocalTouchPos.x < gridSize.width) // Third Column
    {
        column = 3;
    }

    // Check which row the user has clicked
    if (gridLocalTouchPos.y < gridSectionSize.y) // First Row
    {
        row = 1;
    }
    else if (gridLocalTouchPos.y < gridSectionSize.y * 2) // Second Row
    {
        row = 2;
    }
    else if (gridLocalTouchPos.y < gridSize.height) // Third Row
    {
        row = 3;
    }

//    if (_gridArray[column - 1][row - 1] == EMPTY_PIECE)
    {
//        _gridArray[column - 1][row - 1] = turn;

//        if (PLAYER_PIECE == turn)
        {
//            _gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));

//            this->CheckHasPlayerWon(turn);
        }

//        _gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
    }
}

void GameState::CheckHasPlayerWon(int player)
{}


void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck)
{
////    if (pieceToCheck == _gridArray[x1][y1] && pieceToCheck == _gridArray[x2][y2] && pieceToCheck == _gridArray[x3][y3])
//    {
//        std::string winningPieceStr;
//
//        if (O_PIECE == pieceToCheck)
//        {
//            winningPieceStr = "O Winning Piece";
//        }
//        else
//        {
//            winningPieceStr = "X Winning Piece";
//        }
//
////        _gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
////        _gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
////        _gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));
//
//
//        if (PLAYER_PIECE == pieceToCheck)
//        {
//            gameState = STATE_WON;
//        }
//        else
//        {
//            gameState = STATE_LOSE;
//        }
//    }
}