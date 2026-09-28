#include "DifficultyMenuState.hpp"

#include "GameContext.hpp"
#include "Layout.hpp"
#include "WindowUtils.hpp"
#include "gui/Button.hpp"
#include "gui/TopBar.hpp"
#include "managers/ResourceIdentifiers.hpp"

namespace {
    constexpr int kWindowTilesX = 7;
    constexpr int kWindowTilesY = 13;

    constexpr int kButtonTilesX = 5;
    constexpr int kButtonTilesY = 1;
}

DifficultyMenuState::DifficultyMenuState(GameContext& context)
    : State(context) {}

void DifficultyMenuState::init() {
    constexpr auto windowSize = Layout::toWindowSize(kWindowTilesX, kWindowTilesY);
    resizeWindow(getContext().window, windowSize);

    auto& backgroundTexture = getContext().assets.getTexture(TextureID::Background);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect(Layout::getRect(0, 0, kWindowTilesX, kWindowTilesY));

    const auto topBar = std::make_shared<TopBar>(getContext(), kWindowTilesX);

    const auto& buttonsTexture = getContext().assets.getTexture(TextureID::DifficultyMenuButtons);

    const auto easyModeButton = std::make_shared<Button>();
    easyModeButton->setTexture(buttonsTexture);
    easyModeButton->setNormalTextureRect(Layout::getRect(0, 0, kButtonTilesX, kButtonTilesY));
    easyModeButton->setSelectedTextureRect(Layout::getRect(5, 0, kButtonTilesX, kButtonTilesY));
    easyModeButton->setPosition(Layout::toPixels(1, 3));
    easyModeButton->setCallback([this]() {
        getContext().difficulty = Difficulty::create(Difficulty::Preset::Easy);
        getContext().states.changeState(StateID::Game);
    });


    const auto normalModeButton = std::make_shared<Button>();
    normalModeButton->setTexture(buttonsTexture);
    normalModeButton->setNormalTextureRect(Layout::getRect(0, 1, kButtonTilesX, kButtonTilesY));
    normalModeButton->setSelectedTextureRect(Layout::getRect(5, 1, kButtonTilesX, kButtonTilesY));
    normalModeButton->setPosition(Layout::toPixels(1, 5));
    normalModeButton->setCallback([this]() {
        getContext().difficulty = Difficulty::create(Difficulty::Preset::Medium);
        getContext().states.changeState(StateID::Game);
    });

    const auto hardModeButton = std::make_shared<Button>();
    hardModeButton->setTexture(buttonsTexture);
    hardModeButton->setNormalTextureRect(Layout::getRect(0, 2, kButtonTilesX, kButtonTilesY));
    hardModeButton->setSelectedTextureRect(Layout::getRect(5, 2, kButtonTilesX, kButtonTilesY));
    hardModeButton->setPosition(Layout::toPixels(1, 7));
    hardModeButton->setCallback([this]() {
        getContext().difficulty = Difficulty::create(Difficulty::Preset::Hard);
        getContext().states.changeState(StateID::Game);
    });

    const auto customModeButton = std::make_shared<Button>();
    customModeButton->setTexture(buttonsTexture);
    customModeButton->setNormalTextureRect(Layout::getRect(0, 3, kButtonTilesX, kButtonTilesY));
    customModeButton->setSelectedTextureRect(Layout::getRect(5, 3, kButtonTilesX, kButtonTilesY));
    customModeButton->setPosition(Layout::toPixels(1, 9));
    customModeButton->setCallback([this]() {
        getContext().states.changeState(StateID::CustomDifficulty);
    });

    mGuiContainer.pack(topBar);
    mGuiContainer.pack(customModeButton);
    mGuiContainer.pack(easyModeButton);
    mGuiContainer.pack(normalModeButton);
    mGuiContainer.pack(hardModeButton);
}

void DifficultyMenuState::handleInput() {
    while (const std::optional<sf::Event> event = getContext().window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            getContext().window.close();
            return;
        }
        mGuiContainer.handleEvent(*event);
    }
}


void DifficultyMenuState::update() {}

void DifficultyMenuState::draw() {
    getContext().window.clear(sf::Color(30, 30, 30));

    getContext().window.draw(mBackground);
    getContext().window.draw(mGuiContainer);

    getContext().window.display();
}
