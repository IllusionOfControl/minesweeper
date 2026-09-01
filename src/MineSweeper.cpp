#include "MineSweeper.hpp"

#include "states/DifficultyMenuState.hpp"
#include "states/EmptyState.hpp"
#include "states/MainMenuState.hpp"
#include "states/AboutState.hpp"

MineSweeper::MineSweeper()
    : mWindow(sf::VideoMode({200, 300}), "MineSweeper", sf::Style::Close | sf::Style::Titlebar)
      , mAssets()
      , mDifficulty(Difficulty::create(Difficulty::Preset::Easy))
      , mContext(mWindow, mAssets, mStateManager, mDifficulty)
      , mStateManager(mContext) {
    loadAssets();
    registerStates();

    mStateManager.changeState(StateID::MainMenu);
}

void MineSweeper::run() {
    while (mWindow.isOpen()) {
        mStateManager.processStateChanges();

        State* activeState = mStateManager.getActiveState();
        if (!activeState) { break; }

        activeState->handleInput();
        activeState->update();
        activeState->draw();
    }
    // mData->assets.loadTexture("tile_texture", "_Resources/res/tiles.png");
    // mData->assets.loadTexture("logo", "_Resources/res/logo.png");

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

void MineSweeper::loadAssets() {
    mAssets.loadTexture(TextureID::Background, "_Resources/res/background.png");
    mAssets.loadTexture(TextureID::Logo, "_Resources/res/logo.png");
    mAssets.loadTexture(TextureID::MainMenuButtons, "_Resources/res/mainMenuButtons.png");
    mAssets.loadTexture(TextureID::DifficultyMenuButtons, "_Resources/res/difficultyMenuButtons.png");
    mAssets.loadTexture(TextureID::AboutButtons, "_Resources/res/aboutButtons.png");
    mAssets.loadTexture(TextureID::TopBarButtons, "_Resources/res/topBarButtons.png");
}

void MineSweeper::registerStates() {
    mStateManager.registerState<EmptyState>(StateID::Empty);
    mStateManager.registerState<MainMenuState>(StateID::MainMenu);
    mStateManager.registerState<DifficultyMenuState>(StateID::DifficultyMenu);
    mStateManager.registerState<AboutState>(StateID::About);
}
