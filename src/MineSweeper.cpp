#include "MineSweeper.hpp"

#include "states/EmptyState.hpp"

MineSweeper::MineSweeper()
    : mWindow(sf::VideoMode({200, 300}), "MineSweeper", sf::Style::Close | sf::Style::Titlebar)
      , mAssets()
      , mDifficulty(Difficulty::create(Difficulty::Preset::Easy))
      , mContext(mWindow, mAssets, mStateManager, mDifficulty)
      , mStateManager(mContext) {
    loadAssets();
    registerStates();

    mStateManager.changeState(StateID::Empty);
}

void MineSweeper::run() {
    while (mWindow.isOpen()) {
        mStateManager.processStateChanges();

        State* activeState = mStateManager.getActiveState();
        if (!activeState) {
            break;
        }

        activeState->handleInput();
        activeState->update();
        activeState->draw();
    }
    // mData->assets.loadTexture("tile_texture", "_Resources/res/tiles.png");
    // mData->assets.loadTexture("logo", "_Resources/res/logo.png");
    // mData->assets.loadTexture("background", "_Resources/res/tiles.png",
    //                                 sf::IntRect(15 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    // mData->assets.loadTexture("smiles_button", "_Resources/res/smiles.png");
    // mData->assets.loadTexture(TEXTURE_SECOND_NAME, "_Resources/res/second.png");
    // mData->assets.loadTexture("customDifficultyButtons", "_Resources/res/second_edited.png",
    //                                 sf::IntRect(0, 128, 320, 352));
    // mData->assets.loadTexture("difficultMenuButtons", "_Resources/res/second_edited.png",
    //                                 sf::IntRect(0, 0, 320, 128));
    // mData->assets.loadTexture("state_buttons", "_Resources/res/state_buttons.png");
    // mData->assets.loadTexture("mainmenu_buttons", "_Resources/res/mainMenuButtons.png");
    // mData->assets.loadTexture("led_background", "_Resources/res/tiles.png",
    //                                 sf::IntRect(16 * SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE));
    //
    // mData->assets.loadFont("default_font", "_Resources/fonts/visitor1.ttf");
}

void MineSweeper::loadAssets() {}

void MineSweeper::registerStates() {
    mStateManager.registerState<EmptyState>(StateID::Empty);
}
