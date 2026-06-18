#include "MineSweeper.hpp"
#include "states/MainMenuState.hpp"

MineSweeper::MineSweeper() {
    mData->window.create(sf::VideoMode(200, 300), "MineSweeper", sf::Style::Close | sf::Style::Titlebar);
    mData->manager.addState(StateRef(new MainMenuState(mData)));

    run();
}

void MineSweeper::run() {
    mData->assets.loadTexture("tile_texture", "_Resources/res/tiles.png");
    mData->assets.loadTexture("logo", "_Resources/res/logo.png");
    mData->assets.loadTexture("background", "_Resources/res/tiles.png",
                                    sf::IntRect(15 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    mData->assets.loadTexture("smiles_button", "_Resources/res/smiles.png");
    mData->assets.loadTexture(TEXTURE_SECOND_NAME, "_Resources/res/second.png");
    mData->assets.loadTexture("customDifficultyButtons", "_Resources/res/second_edited.png",
                                    sf::IntRect(0, 128, 320, 352));
    mData->assets.loadTexture("difficultMenuButtons", "_Resources/res/second_edited.png",
                                    sf::IntRect(0, 0, 320, 128));
    mData->assets.loadTexture("state_buttons", "_Resources/res/state_buttons.png");
    mData->assets.loadTexture("mainmenu_buttons", "_Resources/res/mainMenuButtons.png");
    mData->assets.loadTexture("led_background", "_Resources/res/tiles.png",
                                    sf::IntRect(16 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));

    mData->assets.loadFont("default_font", "_Resources/fonts/visitor1.ttf");

    while (mData->window.isOpen()) {
        mData->manager.processStateChanges();
        mData->manager.getActiveState()->handleInput();
        mData->manager.getActiveState()->update();

        mData->manager.getActiveState()->draw();
    }
}