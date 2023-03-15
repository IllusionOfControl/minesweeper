#include "AboutState.hpp"
#include "../gui/Button.hpp"

AboutState::AboutState(GameDataRef gameData)
        : mGameData(gameData)
        , mGuiContainer() {

}

void AboutState::Init() {
    mGameData->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                             (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                               "Minesweeper",
                               sf::Style::Titlebar | sf::Style::Close);
    auto &backgroundTexture = mGameData->assets.GetTexture("background");
    auto windowSize = mGameData->window.getSize();

    backgroundTexture.setRepeated(true);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto mainMenuButton = std::make_shared<Button>();
    mainMenuButton->setTexture(mGameData->assets.GetTexture("state_buttons"));
    mainMenuButton->setNormalTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setSelectedTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);
    mainMenuButton->setCallback([&]() {
        mGameData->manager.AddState(StateRef(new MainMenuState(mGameData)), true);
    });

    auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(mGameData->assets.GetTexture("state_buttons"));
    exitButton->setNormalTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setSelectedTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setPosition((WIDTH + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);
    exitButton->setCallback([&]() {
        mGameData->window.close();
    });

    auto authorButton = std::make_shared<Button>();
    authorButton->setTexture(mGameData->assets.GetTexture(TEXTURE_SECOND_NAME));
    authorButton->setNormalTextureRect({0 * SQUARE_SIZE, 3 * SQUARE_SIZE, 160, 64});
    authorButton->setSelectedTextureRect({5 * SQUARE_SIZE, 3 * SQUARE_SIZE, 160, 64});
    authorButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);

    mLogo.setTexture(mGameData->assets.GetTexture(TEXTURE_SECOND_NAME));
    mLogo.setTextureRect({0 * SQUARE_SIZE, 1 * SQUARE_SIZE, 160, 32});
    mLogo.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, 1 * SQUARE_SIZE);

    mGuiContainer.pack(mainMenuButton);
    mGuiContainer.pack(exitButton);
    mGuiContainer.pack(authorButton);
}

void AboutState::HandleInput() {
    sf::Event event;

    while (mGameData->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);
    }
}

void AboutState::Update() {

}

void AboutState::Draw() {
    mGameData->window.clear(sf::Color::Red);

    mGameData->window.draw(mBackground);
    mGameData->window.draw(mLogo);
    mGameData->window.draw(mGuiContainer);

    mGameData->window.display();
}