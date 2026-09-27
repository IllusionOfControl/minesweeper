#include "MineSweeper.hpp"

#include "states/DifficultyMenuState.hpp"
#include "states/EmptyState.hpp"
#include "states/MainMenuState.hpp"
#include "states/AboutState.hpp"
#include "states/CustomDifficultyState.hpp"
#include "states/GameState.hpp"
#include "states/SaveResultState.hpp"
#include "Layout.hpp"

MineSweeper::MineSweeper(const StateID initialState)
    : mWindow(sf::VideoMode({200, 300}), "MineSweeper", sf::Style::Close | sf::Style::Titlebar)
      , mStateManager(mContext)
      , mDifficulty(Difficulty::create(Difficulty::Preset::Easy))
      , mContext(mWindow, mAssets, mStateManager, mDifficulty) {
    loadAssets();
    registerStates();

    mStateManager.changeState(initialState);
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
}

void MineSweeper::loadAssets() {
    mAssets.loadTexture(TextureID::Background, "_Resources/res/background.png");
    mAssets.loadTexture(TextureID::Logo, "_Resources/res/logo.png");
    mAssets.loadTexture(TextureID::MainMenuButtons, "_Resources/res/mainMenuButtons.png");
    mAssets.loadTexture(TextureID::DifficultyMenuButtons, "_Resources/res/difficultyMenuButtons.png");
    mAssets.loadTexture(TextureID::AboutButtons, "_Resources/res/aboutButtons.png");
    mAssets.loadTexture(TextureID::TopBarButtons, "_Resources/res/topBarButtons.png");
    mAssets.loadTexture(TextureID::CustomDifficultyButtons, "_Resources/res/second_edited.png",
                        sf::IntRect({0, 128}, {320, 352}));
    mAssets.loadTexture(TextureID::Tiles, "_Resources/res/tiles.png");
    mAssets.loadTexture(TextureID::Smiles, "_Resources/res/smiles.png");
    mAssets.loadTexture(TextureID::LedBackground, "_Resources/res/tiles.png",
                        sf::IntRect({16 * Layout::TileSize, 0}, {Layout::TileSize, Layout::TileSize}));
    mAssets.loadTexture(TextureID::SaveRecordState, "_Resources/res/saveRecordState.png");

    mAssets.loadFont(FontID::Default, "_Resources/fonts/visitor1.ttf");
}

void MineSweeper::registerStates() {
    mStateManager.registerState<EmptyState>(StateID::Empty);
    mStateManager.registerState<MainMenuState>(StateID::MainMenu);
    mStateManager.registerState<DifficultyMenuState>(StateID::DifficultyMenu);
    mStateManager.registerState<AboutState>(StateID::About);
    mStateManager.registerState<CustomDifficultyState>(StateID::CustomDifficulty);
    mStateManager.registerState<GameState>(StateID::Game);
    mStateManager.registerState<SaveResultState>(StateID::SaveResult);
}
