#include "DifficultyMenuState.hpp"

#include "GameContext.hpp"
#include "Layout.hpp"
#include "WindowUtils.hpp"
#include "gui/Button.hpp"
#include "gui/TopBar.hpp"
#include "managers/ResourceIdentifiers.hpp"

namespace {
    constexpr int kWindowTilesX = 7;
    constexpr int kWindowTilesY = 12;

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

    const auto& buttonsTexture = getContext().assets.getTexture(TextureID::DifficultyMenuButtons);

    const auto easyModeButton = std::make_shared<Button>();
    easyModeButton->setTexture(buttonsTexture);
    easyModeButton->setNormalTextureRect(Layout::getRect(0, 0, kButtonTilesX, kButtonTilesY));
    easyModeButton->setSelectedTextureRect(Layout::getRect(5, 0, kButtonTilesX, kButtonTilesY));
    easyModeButton->setPosition(Layout::toPixels(1, 3));
    easyModeButton->setCallback([this]() {
        // mContext->difficulty = DIFFICULTY_EASY;
        // mContext->manager.addState(StateRef(new GameState(mContext)), true);
    });


    auto normalModeButton = std::make_shared<Button>();
    normalModeButton->setTexture(buttonsTexture);
    normalModeButton->setNormalTextureRect(Layout::getRect(0, 1, kButtonTilesX, kButtonTilesY));
    normalModeButton->setSelectedTextureRect(Layout::getRect(5, 1, kButtonTilesX, kButtonTilesY));
    normalModeButton->setPosition(Layout::toPixels(1, 5));
    normalModeButton->setCallback([this]() {
        // mContext->difficulty = DIFFICULTY_MEDIUM;
        // mContext->manager.addState(StateRef(new GameState(mContext)), true);
    });

    auto hardModeButton = std::make_shared<Button>();
    hardModeButton->setTexture(buttonsTexture);
    hardModeButton->setNormalTextureRect(Layout::getRect(0, 2, kButtonTilesX, kButtonTilesY));
    hardModeButton->setSelectedTextureRect(Layout::getRect(5, 2, kButtonTilesX, kButtonTilesY));
    hardModeButton->setPosition(Layout::toPixels(1, 7));
    hardModeButton->setCallback([this]() {
        // mContext->difficulty = DIFFICULTY_HARD;
        // mContext->manager.addState(StateRef(new GameState(mContext)), true);
    });
    //
    auto customModeButton = std::make_shared<Button>();
    customModeButton->setTexture(buttonsTexture);
    customModeButton->setNormalTextureRect(Layout::getRect(0, 3, kButtonTilesX, kButtonTilesY));
    customModeButton->setSelectedTextureRect(Layout::getRect(5, 3, kButtonTilesX, kButtonTilesY));
    customModeButton->setPosition(Layout::toPixels(1, 9));
    customModeButton->setCallback([this]() {
        // mContext->manager.addState(StateRef(new CustomDifficultyState(mContext)), true);
    });

    const auto topBar = std::make_shared<TopBar>(getContext(), kWindowTilesX);

    // mGuiContainer.pack(mainMenuButton);
    // mGuiContainer.pack(exitButton);
    mGuiContainer.pack(customModeButton);
    mGuiContainer.pack(easyModeButton);
    mGuiContainer.pack(normalModeButton);
    mGuiContainer.pack(hardModeButton);
    mGuiContainer.pack(topBar);
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
    getContext().window.clear(sf::Color::Red);

    getContext().window.draw(mBackground);
    getContext().window.draw(mGuiContainer);

    getContext().window.display();
}
