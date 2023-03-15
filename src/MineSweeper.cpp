#include "MineSweeper.hpp"
#include "states/MainMenuState.hpp"

MineSweeper::MineSweeper() {
    _data->window.create(sf::VideoMode(200, 300), "MineSweeper", sf::Style::Close | sf::Style::Titlebar);
    _data->manager.AddState(StateRef(new MainMenuState(this->_data)));

    this->Run();
}

void MineSweeper::Run() {
    srand((unsigned int) time(nullptr));
    this->_data->assets.LoadTexture("tile_texture", "_Resources/res/tiles.png");
    this->_data->assets.LoadTexture("logo", "_Resources/res/logo.png");
    this->_data->assets.LoadTexture("option_buttons", "_Resources/res/tiles.png");
    this->_data->assets.LoadTexture("background", "_Resources/res/tiles.png", sf::IntRect(15 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    this->_data->assets.LoadTexture("text_background", "_Resources/res/tiles.png", sf::IntRect(16 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    this->_data->assets.LoadTexture("smiles_button", "_Resources/res/smiles.png");
    this->_data->assets.LoadTexture(TEXTURE_SECOND_NAME, "_Resources/res/second.png");
    this->_data->assets.LoadTexture("customDifficultyButtons", "_Resources/res/second_edited.png", sf::IntRect(0, 128, 320, 352));
    this->_data->assets.LoadTexture("difficultMenuButtons", "_Resources/res/second_edited.png", sf::IntRect(0, 0, 320, 128));
    this->_data->assets.LoadTexture("state_buttons", "_Resources/res/state_buttons.png");
    this->_data->assets.LoadTexture("mainmenu_buttons", "_Resources/res/mainMenuButtons.png");
    this->_data->assets.LoadTexture("led_background", "_Resources/res/tiles.png", sf::IntRect(16 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    this->_data->assets.LoadTexture("leaderboard", "_Resources/res/leaderboard.png");

    this->_data->assets.LoadFont("default_font", "_Resources/fonts/visitor1.ttf");

    while (this->_data->window.isOpen()) {
        this->_data->manager.ProcessStateChanges();
        this->_data->manager.GetActiveState()->HandleInput();
        this->_data->manager.GetActiveState()->Update();

        this->_data->manager.GetActiveState()->Draw();
    }
}