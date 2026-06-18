#include "AboutState.hpp"
#include "../gui/Button.hpp"
#include "../gui/WidgetFactory.hpp"
#include "../WindowUtils.hpp"

AboutState::AboutState(GameDataRef context)
        : mContext(context)
        , mGuiContainer() {

}

void AboutState::init() {
    resizeWindow(mContext->window,
                 (WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                 (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE);
    widgets::setupBackground(mBackground, mContext);

    auto mainMenuButton = widgets::makeMainMenuButton(mContext);
    auto exitButton = widgets::makeExitButton(mContext, WIDTH);

    auto authorButton = std::make_shared<Button>();
    authorButton->setTexture(mContext->assets.getTexture(TEXTURE_SECOND_NAME));
    authorButton->setNormalTextureRect({0 * SQUARE_SIZE, 3 * SQUARE_SIZE, 160, 64});
    authorButton->setSelectedTextureRect({5 * SQUARE_SIZE, 3 * SQUARE_SIZE, 160, 64});
    authorButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);

    mLogo.setTexture(mContext->assets.getTexture(TEXTURE_SECOND_NAME));
    mLogo.setTextureRect({0 * SQUARE_SIZE, 1 * SQUARE_SIZE, 160, 32});
    mLogo.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, 1 * SQUARE_SIZE);

    mGuiContainer.pack(mainMenuButton);
    mGuiContainer.pack(exitButton);
    mGuiContainer.pack(authorButton);
}

void AboutState::handleInput() {
    sf::Event event;

    while (mContext->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);
    }
}

void AboutState::update() {

}

void AboutState::draw() {
    mContext->window.clear(sf::Color::Red);

    mContext->window.draw(mBackground);
    mContext->window.draw(mLogo);
    mContext->window.draw(mGuiContainer);

    mContext->window.display();
}