#include "AboutState.hpp"
#include "../gui/Button.hpp"

AboutState::AboutState(GameDataRef context)
        : mContext(context)
        , mGuiContainer() {

}

void AboutState::Init() {
    mContext->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                             (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                            "Minesweeper",
                               sf::Style::Titlebar | sf::Style::Close);
    auto &backgroundTexture = mContext->assets.GetTexture("background");
    auto windowSize = mContext->window.getSize();

    backgroundTexture.setRepeated(true);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto mainMenuButton = std::make_shared<Button>();
    mainMenuButton->setTexture(mContext->assets.GetTexture("state_buttons"));
    mainMenuButton->setNormalTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setSelectedTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);
    mainMenuButton->setCallback([&]() {
        mContext->manager.AddState(StateRef(new MainMenuState(mContext)), true);
    });

    auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(mContext->assets.GetTexture("state_buttons"));
    exitButton->setNormalTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setSelectedTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setPosition((WIDTH + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);
    exitButton->setCallback([&]() {
        mContext->window.close();
    });

    auto authorButton = std::make_shared<Button>();
    authorButton->setTexture(mContext->assets.GetTexture(TEXTURE_SECOND_NAME));
    authorButton->setNormalTextureRect({0 * SQUARE_SIZE, 3 * SQUARE_SIZE, 160, 64});
    authorButton->setSelectedTextureRect({5 * SQUARE_SIZE, 3 * SQUARE_SIZE, 160, 64});
    authorButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);

    mLogo.setTexture(mContext->assets.GetTexture(TEXTURE_SECOND_NAME));
    mLogo.setTextureRect({0 * SQUARE_SIZE, 1 * SQUARE_SIZE, 160, 32});
    mLogo.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, 1 * SQUARE_SIZE);

    mGuiContainer.pack(mainMenuButton);
    mGuiContainer.pack(exitButton);
    mGuiContainer.pack(authorButton);
}

void AboutState::HandleInput() {
    sf::Event event;

    while (mContext->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);
    }
}

void AboutState::Update() {

}

void AboutState::Draw() {
    mContext->window.clear(sf::Color::Red);

    mContext->window.draw(mBackground);
    mContext->window.draw(mLogo);
    mContext->window.draw(mGuiContainer);

    mContext->window.display();
}