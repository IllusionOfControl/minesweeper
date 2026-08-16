#include "MainMenuState.hpp"
#include "GameContext.hpp"
#include "Layout.hpp"
#include "WindowUtils.hpp"
#include "gui/Button.hpp"
#include "managers/ResourceIdentifiers.hpp"

namespace {
    constexpr int kMenuWidth = 7;
    constexpr int kMenuHeight = 12;

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
    playButton->setSelectedTextureRect(Layout::getRect(5, 0, kButtonWidth, kButtonHeight));
    playButton->setCallback([this]() { getContext().states.changeState(StateID::Empty); });
    playButton->setPosition(Layout::toPixels(1, 5));

    const auto aboutButton = std::make_shared<Button>();
    aboutButton->setTexture(buttonTextures);
    aboutButton->setNormalTextureRect(Layout::getRect(0, 1, kButtonWidth, kButtonHeight));
    aboutButton->setSelectedTextureRect(Layout::getRect(5, 1, kButtonWidth, kButtonHeight));
    aboutButton->setCallback([this]() { getContext().states.changeState(StateID::Empty); });
    aboutButton->setPosition(Layout::toPixels(1, 7));

    const auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(buttonTextures);
    exitButton->setNormalTextureRect(Layout::getRect(0, 2, kButtonWidth, kButtonHeight));
    exitButton->setSelectedTextureRect(Layout::getRect(5, 2, kButtonWidth, kButtonHeight));
    exitButton->setCallback([this]() { getContext().window.close(); });
    exitButton->setPosition(Layout::toPixels(1,9));

    mLogo.setPosition(Layout::toPixels(1, 1));
    mLogo.setTexture(getContext().assets.getTexture(TextureID::Logo));

    mGuiContainer.pack(playButton);
    mGuiContainer.pack(aboutButton);
    mGuiContainer.pack(exitButton);
}

void MainMenuState::handleInput() {
    while (const std::optional<sf::Event> event = getContext().window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            getContext().window.close();
            return;
        }
        mGuiContainer.handleEvent(*event);
    }
}

void MainMenuState::update() {}

void MainMenuState::draw() {
    getContext().window.clear(sf::Color::Red);

    getContext().window.draw(mBackground);
    getContext().window.draw(mLogo);
    getContext().window.draw(mGuiContainer);

    getContext().window.display();
}
