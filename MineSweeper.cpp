#include "MineSweeper.h"
#include "states/MainMenuState.h"
#include "header.h"

MineSweeper::MineSweeper()
{
    _data->window.create(sf::VideoMode(200, 300), "MineSweeper", sf::Style::Close | sf::Style::Titlebar);
    _data->manager.AddState(StateRef(new MainMenuState(this->_data)));

    this->Run();
}

void MineSweeper::Run()
{

    this->_data->assets.LoadTexture("tile_texture", "images/tiles.png");
    this->_data->assets.LoadTexture("logo", "images/logo.png");
    this->_data->assets.LoadTexture("option_buttons", "images/tiles.png");
    this->_data->assets.LoadTexture("background", "images/tiles.png", sf::IntRect(16 * squareSize, 0, squareSize, squareSize));
    this->_data->assets.LoadTexture("face_button", "images/faces.png");
    this->_data->assets.LoadTexture(TEXTURE_SECOND_NAME, "images/second.png");

    this->_data->assets.LoadFont("default_font", "fonts/visitor1.ttf");

    while (this->_data->window.isOpen()) {
        this->_data->manager.ProcessStateChanges();
        this->_data->manager.GetActiveState()->HandleInput();
        this->_data->manager.GetActiveState()->Update();

        this->_data->manager.GetActiveState()->Draw();
    }
}