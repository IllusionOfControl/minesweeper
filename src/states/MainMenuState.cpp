#include "MainMenuState.h"
#include "../gui/Button.hpp"

MainMenuState::MainMenuState(GameDataRef gameData)
        : mGameData(gameData)
        , mGuiContainer() {

}

void MainMenuState::Init() {
    mGameData->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                       (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                             "Minesweeper",
                         sf::Style::Titlebar | sf::Style::Close);
    auto &backgroundTexture = mGameData->assets.GetTexture("background");
    auto windowSize = mGameData->window.getSize();

    backgroundTexture.setRepeated(true);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto &buttonTextures = mGameData->assets.GetTexture("mainmenu_buttons");

    auto playButton = std::make_shared<Button>();
    playButton->setTexture(buttonTextures);
    playButton->setNormalTextureRect(BUTTON_INT_RECT(0, 0));
    playButton->setSelectedTextureRect(BUTTON_INT_RECT(1, 0));
    playButton->setCallback([&]() {
        mGameData->manager.AddState(StateRef(new DifficultyMenuState(mGameData)), true);
    });
    playButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);

    auto aboutButton = std::make_shared<Button>();
    aboutButton->setTexture(buttonTextures);
    aboutButton->setNormalTextureRect(BUTTON_INT_RECT(0, 1));
    aboutButton->setSelectedTextureRect(BUTTON_INT_RECT(1, 1));
    aboutButton->setCallback([&]() {
        mGameData->manager.AddState(StateRef(new AboutState(mGameData)), true);
    });
    aboutButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);

    auto leaderboardsButton = std::make_shared<Button>();
    leaderboardsButton->setTexture(buttonTextures);
    leaderboardsButton->setNormalTextureRect(BUTTON_INT_RECT(0, 3));
    leaderboardsButton->setSelectedTextureRect(BUTTON_INT_RECT(1, 3));
    leaderboardsButton->setCallback([&]() {
        mGameData->manager.AddState(StateRef(new LeaderboardState(mGameData)), true);
    });
    leaderboardsButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 4) * SQUARE_SIZE);

    auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(buttonTextures);
    exitButton->setNormalTextureRect(BUTTON_INT_RECT(0, 2));
    exitButton->setSelectedTextureRect(BUTTON_INT_RECT(1, 2));
    exitButton->setCallback([&]() {
        mGameData->window.close();
    });
    exitButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 6) * SQUARE_SIZE);

    mLogo.setPosition(32, 0);
    mLogo.setTexture(mGameData->assets.GetTexture("logo"));

    mGuiContainer.pack(playButton);
    mGuiContainer.pack(aboutButton);
    mGuiContainer.pack(leaderboardsButton);
    mGuiContainer.pack(exitButton);
}

void MainMenuState::HandleInput() {
    sf::Event event;

    while (mGameData->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);
    }
}

void MainMenuState::Update() {

}

void MainMenuState::Draw() {
    mGameData->window.clear(sf::Color::Red);

    mGameData->window.draw(mBackground);
    mGameData->window.draw(mGuiContainer);
    mGameData->window.draw(mLogo);

    mGameData->window.display();
}