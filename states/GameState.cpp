#include "GameState.h"

#include <sstream>
#include "GameState.h"
#include "MainMenuState.h"
#include "../DEFINITIONS.h"
//#include "GameOverState.hpp"

#include <iostream>

GameState::GameState(GameDataRef data) : _data(data)
{

}

void GameState::Init()
{
    gameState = STATE_PLAYING;

    int window_h = TILE_WIDTH * 11;
    int window_w = TILE_HEIGHT * 11;
    this->_data->window.create(sf::VideoMode(TILE_WIDTH * 12, TILE_HEIGHT * 12), "MineSweeper", sf::Style::Close | sf::Style::Titlebar);
    this->_data->assets.LoadTexture("tile_0", GAME_FIELD_TILES, TILE_0);
    this->_data->assets.LoadTexture("tile_1", GAME_FIELD_TILES, TILE_1);
    this->_data->assets.LoadTexture("tile_2", GAME_FIELD_TILES, TILE_2);
    this->_data->assets.LoadTexture("tile_3", GAME_FIELD_TILES, TILE_3);
    this->_data->assets.LoadTexture("tile_4", GAME_FIELD_TILES, TILE_4);
    this->_data->assets.LoadTexture("tile_5", GAME_FIELD_TILES, TILE_5);
    this->_data->assets.LoadTexture("tile_6", GAME_FIELD_TILES, TILE_6);
    this->_data->assets.LoadTexture("tile_7", GAME_FIELD_TILES, TILE_7);
    this->_data->assets.LoadTexture("tile_8", GAME_FIELD_TILES, TILE_8);
    this->_data->assets.LoadTexture("tile_bomb", GAME_FIELD_TILES, TILE_BOMB);
    this->_data->assets.LoadTexture("tile_bomb_detonated", GAME_FIELD_TILES, TILE_BOMB_DETONATED);
    this->_data->assets.LoadTexture("tile_mine_bomb_false", GAME_FIELD_TILES, TILE_BOMB_FALSE);
    this->_data->assets.LoadTexture("tile_flag", GAME_FIELD_TILES, TILE_FLAG);
    this->_data->assets.LoadTexture("tile_question", GAME_FIELD_TILES, TILE_QUESTION);
    this->_data->assets.LoadTexture("tile_block", GAME_FIELD_TILES, TILE_BLOCK);
    this->_data->assets.LoadTexture("tile_closed", GAME_FIELD_TILES, TILE_CLOSED);


    this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
    this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
    this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
    this->_data->assets.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
    this->_data->assets.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

    auto& backgroundTexture = this->_data->assets.GetTexture("tile_block");
    backgroundTexture.setRepeated(true);
    this->_background.setTexture(backgroundTexture);
    this->_background.setTextureRect({0,0, TILE_WIDTH * 12, TILE_HEIGHT * 12});

    this->_gridSprite.setTexture(this->_data->assets.GetTexture("tile_closed"));
    this->_gridSprite.setTextureRect({TILE_HEIGHT * 1,
                                      TILE_WIDTH * 1,
                                      this->_data->difficulty.field_height * TILE_HEIGHT,
                                     this->_data->difficulty.field_height * TILE_WIDTH});
    this->_gridSprite.setPosition(sf::Vector2f(TILE_HEIGHT * 1, TILE_WIDTH * 1));

//    _pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
//    _gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

    //InitGridPieces();
    InitGridArray();
}

void GameState::HandleInput()
{
    sf::Event event;

    while (this->_data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            this->_data->window.close();
        }

        if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
        {
            // Switch To Game State
            //this->_data->manager.AddState(StateRef(new PauseState(_data)), false);
        }
        else if (this->_data->input.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
        {
            if (STATE_PLAYING == gameState)
            {
                this->CheckAndPlacePiece();
            }
        }
    }
}

void GameState::Update()
{
}

void GameState::Draw()
{
    this->_data->window.clear(sf::Color::Red);

    this->_data->window.draw( this->_background );

    this->_data->window.draw( this->_pauseButton );

    this->_data->window.draw( this->_gridSprite );

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            //this->_data->window.draw(this->_gridPieces[x][y]);
        }
    }

    this->_data->window.display();
}

void GameState::InitGridPieces()
{
    sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
//            _gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
//            _gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7, _gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);
//            _gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
        }
    }
}

void GameState::InitGridCells() {
    sf::Vector2i tempSpriteSize = sf::Vector2i(TILE_WIDTH, TILE_HEIGHT);
    sf::Vector2f basePos = this->_gridSprite.getPosition();
    int grid_w = this->_data->difficulty.field_width;
    int grid_h = this->_data->difficulty.field_height;
    for (int i = 0; i < grid_h * grid_w; i++) {
        sf::Sprite cell;
        cell.setTexture(this->_data->assets.GetTexture("tile_closed"));
        //cell.setPosition()
        this->_gridCells.push_back(cell);
    }
}

void GameState::InitGridArray() {
    int cellCount = this->_data->difficulty.field_height * this->_data->difficulty.field_width;
    for (int i = 0; i < cellCount; i++) {
        this->_gridArray.push_back(0);
    }

    for (int i = 0; i < this->_data->difficulty.field_height; i++) {
        int rand_x = rand() % this->_data->difficulty.field_width;
        int rand_y = rand() % this->_data->difficulty.field_height;
        int cellNum = rand_y * this->_data->difficulty.field_height + rand_x;
        if (this->_gridArray.at(i) == CELL_BOMB) {
            i--;
            continue;
        }
        this->_gridArray[cellNum] = CELL_BOMB;
        if (rand_x != 0) _gridArray[cellNum-1]++;
        if (rand_x != this->_data->difficulty.field_width) _gridArray[cellNum+1]++;
        if (rand_x != 0) _gridArray[cellNum+this->_data->difficulty.field_height]++;
        if (rand_y != this->_data->difficulty.field_height) _gridArray[cellNum-this->_data->difficulty.field_height]++;
    }
}



void GameState::CheckAndPlacePiece()
{
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
{
    Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
    Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
    Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
    Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
    Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
    Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
    Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
    Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);

    if (STATE_WON != gameState)
    {

        Check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
        Check3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_PIECE);
        Check3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_PIECE);
        Check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
        Check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
        Check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
        Check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
        Check3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_PIECE);
    }

    int emptyNum = 9;

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
//            if (EMPTY_PIECE != _gridArray[x][y])
            {
//                emptyNum--;
            }
        }
    }

//    // check if the game is a draw
//    if (0 == emptyNum && (STATE_WON != gameState) && (STATE_LOSE != gameState))
//    {
//        gameState = STATE_DRAW;
//    }
//
//    // check if the game is over
//    if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState)
//    {
//        // show game over
//        this->_clock.restart( );
//    }

    std::cout << gameState << std::endl;
}

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