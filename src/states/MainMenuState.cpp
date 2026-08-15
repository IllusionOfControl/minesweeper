#include "MainMenuState.hpp"

#include "GameContext.hpp"
#include "Layout.hpp"
#include "WindowUtils.hpp"
#include "gui/Button.hpp"
#include "managers/ResourceIdentifiers.hpp"

namespace {
    constexpr int kMenuWidth = 5;
    constexpr int kMenuHeight = 7;

    constexpr int kButtonWidth = 5;
    constexpr int kButtonHeight = 1;
}

void MainMenuState::init() {
    constexpr auto windowSize = Layout::toWindowSize(kMenuWidth, kMenuHeight);
    resizeWindow(getContext().window, windowSize);

    auto& bg_texture = getContext().assets.getTexture(TextureID::Background);
    mBackground.setTexture(bg_texture);
    mBackground.setTextureRect({{0, 0}, {static_cast<int>(windowSize.x), static_cast<int>(windowSize.y)}});

    const auto& buttonTextures = getContext().assets.getTexture(TextureID::MainMenuButtons);

    const auto playButton = std::make_shared<Button>();
    playButton->setTexture(buttonTextures);
    playButton->setNormalTextureRect(Layout::getRect(0, 0, kButtonWidth, kButtonHeight));
    playButton->setSelectedTextureRect(Layout::getRect(1, 0, kButtonWidth, kButtonHeight));
    playButton->setCallback([this]() {
        getContext().states.changeState(StateID::Empty);
    });
    playButton->setPosition(Layout::toPixels(1, 5));

    // auto aboutButton = std::make_shared<Button>();
    // aboutButton->setTexture(buttonTextures);
    // aboutButton->setNormalTextureRect(BUTTON_INT_RECT(0, 1));
    // aboutButton->setSelectedTextureRect(BUTTON_INT_RECT(1, 1));
    // aboutButton->setCallback([this]() { mContext->manager.addState(StateRef(new AboutState(mContext)), true); });
    // aboutButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);
    //
    // auto exitButton = std::make_shared<Button>();
    // exitButton->setTexture(buttonTextures);
    // exitButton->setNormalTextureRect(BUTTON_INT_RECT(0, 2));
    // exitButton->setSelectedTextureRect(BUTTON_INT_RECT(1, 2));
    // exitButton->setCallback([this]() { mContext->window.close(); });
    // exitButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 6) * SQUARE_SIZE);
    //
    // mLogo.setPosition(32, 0);
    // mLogo.setTexture(mContext->assets.getTexture("logo"));

    mGuiContainer.pack(playButton);
    // mGuiContainer.pack(aboutButton);
    // mGuiContainer.pack(exitButton);
}

void MainMenuState::handleInput() {
    while (const std::optional<sf::Event> event = getContext().window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            getContext().window.close();
            return;
        }
        // mGuiContainer.handleEvent(event);
    }
}

void MainMenuState::update() {}

void MainMenuState::draw() {
    getContext().window.clear(sf::Color::Red);

    getContext().window.draw(mBackground);
    getContext().window.draw(mGuiContainer);
    // mContext->window.draw(mLogo);

    getContext().window.display();
}
