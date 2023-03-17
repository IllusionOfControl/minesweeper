#include "MainMenuState.hpp"

MainMenuState::MainMenuState(GameDataRef context)
        : mContext(context)
        , mGuiContainer() {

}

void MainMenuState::Init() {
    mContext->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                       (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                            "Minesweeper",
                         sf::Style::Titlebar | sf::Style::Close);
    auto &backgroundTexture = mContext->assets.GetTexture("background");
    auto windowSize = mContext->window.getSize();

    backgroundTexture.setRepeated(true);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto &buttonTextures = mContext->assets.GetTexture("mainmenu_buttons");

    auto playButton = std::make_shared<Button>();
    playButton->setTexture(buttonTextures);
    playButton->setNormalTextureRect(BUTTON_INT_RECT(0, 0));
    playButton->setSelectedTextureRect(BUTTON_INT_RECT(1, 0));
    playButton->setCallback([&]() {
        mContext->manager.AddState(StateRef(new DifficultyMenuState(mContext)), true);
    });
    playButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);

    auto aboutButton = std::make_shared<Button>();
    aboutButton->setTexture(buttonTextures);
    aboutButton->setNormalTextureRect(BUTTON_INT_RECT(0, 1));
    aboutButton->setSelectedTextureRect(BUTTON_INT_RECT(1, 1));
    aboutButton->setCallback([&]() {
        mContext->manager.AddState(StateRef(new AboutState(mContext)), true);
    });
    aboutButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);

    auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(buttonTextures);
    exitButton->setNormalTextureRect(BUTTON_INT_RECT(0, 2));
    exitButton->setSelectedTextureRect(BUTTON_INT_RECT(1, 2));
    exitButton->setCallback([&]() {
        mContext->window.close();
    });
    exitButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 6) * SQUARE_SIZE);

    mLogo.setPosition(32, 0);
    mLogo.setTexture(mContext->assets.GetTexture("logo"));

    mGuiContainer.pack(playButton);
    mGuiContainer.pack(aboutButton);
    mGuiContainer.pack(exitButton);
}

void MainMenuState::HandleInput() {
    sf::Event event;

    while (mContext->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);
    }
}

void MainMenuState::Update() {

}

void MainMenuState::Draw() {
    mContext->window.clear(sf::Color::Red);

    mContext->window.draw(mBackground);
    mContext->window.draw(mGuiContainer);
    mContext->window.draw(mLogo);

    mContext->window.display();
}