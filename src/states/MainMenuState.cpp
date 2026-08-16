#include "MainMenuState.hpp"
#include "GameContext.hpp"
#include "Layout.hpp"
#include "WindowUtils.hpp"
#include "gui/Button.hpp"
#include "managers/ResourceIdentifiers.hpp"

namespace {
    constexpr int kWindowTilesX = 7;
    constexpr int kWindowTilesY = 12;

    constexpr int kButtonTilesX = 5;
    constexpr int kButtonTilesY = 1;
}

void MainMenuState::init() {
    constexpr auto windowSize = Layout::toWindowSize(kWindowTilesX, kWindowTilesY);
    resizeWindow(getContext().window, windowSize);

    auto& backgroundTexture = getContext().assets.getTexture(TextureID::Background);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect({{0, 0}, {static_cast<int>(windowSize.x), static_cast<int>(windowSize.y)}});

    const auto& buttonsTexture = getContext().assets.getTexture(TextureID::MainMenuButtons);

    const auto playButton = std::make_shared<Button>();
    playButton->setTexture(buttonsTexture);
    playButton->setNormalTextureRect(Layout::getRect(0, 0, kButtonTilesX, kButtonTilesY));
    playButton->setSelectedTextureRect(Layout::getRect(5, 0, kButtonTilesX, kButtonTilesY));
    playButton->setCallback([this]() { getContext().states.changeState(StateID::DifficultyMenu); });
    playButton->setPosition(Layout::toPixels(1, 5));

    const auto aboutButton = std::make_shared<Button>();
    aboutButton->setTexture(buttonsTexture);
    aboutButton->setNormalTextureRect(Layout::getRect(0, 1, kButtonTilesX, kButtonTilesY));
    aboutButton->setSelectedTextureRect(Layout::getRect(5, 1, kButtonTilesX, kButtonTilesY));
    aboutButton->setCallback([this]() { getContext().states.changeState(StateID::Empty); });
    aboutButton->setPosition(Layout::toPixels(1, 7));

    const auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(buttonsTexture);
    exitButton->setNormalTextureRect(Layout::getRect(0, 2, kButtonTilesX, kButtonTilesY));
    exitButton->setSelectedTextureRect(Layout::getRect(5, 2, kButtonTilesX, kButtonTilesY));
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
