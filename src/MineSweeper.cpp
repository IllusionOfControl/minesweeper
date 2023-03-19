#include "MineSweeper.hpp"
#include "states/MainMenuState.hpp"

MineSweeper::MineSweeper() {
    _data->window.create(sf::VideoMode(200, 300), "MineSweeper", sf::Style::Close | sf::Style::Titlebar);
    _data->manager.addState(StateRef(new MainMenuState(this->_data)));

    this->run();
}

void MineSweeper::run() {
    srand((unsigned int) time(nullptr));
    this->_data->assets.loadTexture("tile_texture", "_Resources/res/tiles.png");
    this->_data->assets.loadTexture("logo", "_Resources/res/logo.png");
    this->_data->assets.loadTexture("option_buttons", "_Resources/res/tiles.png");
    this->_data->assets.loadTexture("background", "_Resources/res/tiles.png",
                                    sf::IntRect(15 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    this->_data->assets.loadTexture("text_background", "_Resources/res/tiles.png",
                                    sf::IntRect(16 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    this->_data->assets.loadTexture("smiles_button", "_Resources/res/smiles.png");
    this->_data->assets.loadTexture(TEXTURE_SECOND_NAME, "_Resources/res/second.png");
    this->_data->assets.loadTexture("customDifficultyButtons", "_Resources/res/second_edited.png",
                                    sf::IntRect(0, 128, 320, 352));
    this->_data->assets.loadTexture("difficultMenuButtons", "_Resources/res/second_edited.png",
                                    sf::IntRect(0, 0, 320, 128));
    this->_data->assets.loadTexture("state_buttons", "_Resources/res/state_buttons.png");
    this->_data->assets.loadTexture("mainmenu_buttons", "_Resources/res/mainMenuButtons.png");
    this->_data->assets.loadTexture("led_background", "_Resources/res/tiles.png",
                                    sf::IntRect(16 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    this->_data->assets.loadTexture("leaderboard", "_Resources/res/leaderboard.png");

    this->_data->assets.LoadFont("default_font", "_Resources/fonts/visitor1.ttf");

    while (this->_data->window.isOpen()) {
        this->_data->manager.processStateChanges();
        this->_data->manager.getActiveState()->handleInput();
        this->_data->manager.getActiveState()->update();

        this->_data->manager.getActiveState()->draw();
    }
}