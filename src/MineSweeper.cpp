#include "MineSweeper.hpp"
#include "states/MainMenuState.hpp"

MineSweeper::MineSweeper() {
    _data->window.create(sf::VideoMode(200, 300), "MineSweeper", sf::Style::Close | sf::Style::Titlebar);
    _data->manager.addState(StateRef(new MainMenuState(_data)));

    run();
}

void MineSweeper::run() {
    srand((unsigned int) time(nullptr));
    _data->assets.loadTexture("tile_texture", "_Resources/res/tiles.png");
    _data->assets.loadTexture("logo", "_Resources/res/logo.png");
    _data->assets.loadTexture("option_buttons", "_Resources/res/tiles.png");
    _data->assets.loadTexture("background", "_Resources/res/tiles.png",
                                    sf::IntRect(15 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    _data->assets.loadTexture("text_background", "_Resources/res/tiles.png",
                                    sf::IntRect(16 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    _data->assets.loadTexture("smiles_button", "_Resources/res/smiles.png");
    _data->assets.loadTexture(TEXTURE_SECOND_NAME, "_Resources/res/second.png");
    _data->assets.loadTexture("customDifficultyButtons", "_Resources/res/second_edited.png",
                                    sf::IntRect(0, 128, 320, 352));
    _data->assets.loadTexture("difficultMenuButtons", "_Resources/res/second_edited.png",
                                    sf::IntRect(0, 0, 320, 128));
    _data->assets.loadTexture("state_buttons", "_Resources/res/state_buttons.png");
    _data->assets.loadTexture("mainmenu_buttons", "_Resources/res/mainMenuButtons.png");
    _data->assets.loadTexture("led_background", "_Resources/res/tiles.png",
                                    sf::IntRect(16 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    _data->assets.loadTexture("leaderboard", "_Resources/res/leaderboard.png");

    _data->assets.LoadFont("default_font", "_Resources/fonts/visitor1.ttf");

    while (_data->window.isOpen()) {
        _data->manager.processStateChanges();
        _data->manager.getActiveState()->handleInput();
        _data->manager.getActiveState()->update();

        _data->manager.getActiveState()->draw();
    }
}