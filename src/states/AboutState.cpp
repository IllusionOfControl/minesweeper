#include "AboutState.hpp"
#include "GameContext.hpp"
#include "WindowUtils.hpp"
#include "Layout.hpp"
#include "gui/Button.hpp"
#include "gui/TopBar.hpp"
#include "gui/Image.hpp"

namespace {
    constexpr int kWindowTilesX = 7;
    constexpr int kWindowTilesY = 13;
}

AboutState::AboutState(GameContext& context)
    : State(context) {}

void AboutState::init() {
    constexpr auto windowSize = Layout::toWindowSize(kWindowTilesX, kWindowTilesY);
    resizeWindow(getContext().window, windowSize);

    auto& backgroundTexture = getContext().assets.getTexture(TextureID::Background);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect(Layout::getRect(0, 0, kWindowTilesX, kWindowTilesY));

    auto& logoTexture = getContext().assets.getTexture(TextureID::Logo);
    const auto logo = std::make_shared<Image>();
    logo->setPosition(Layout::toPixels(1, 2));
    logo->setTexture(logoTexture);

    const auto& buttonsTexture = getContext().assets.getTexture(TextureID::AboutButtons);

    const auto authorButton = std::make_shared<Button>();
    authorButton->setTexture(buttonsTexture);
    authorButton->setNormalTextureRect(Layout::getRect(0, 0, 5, 2));
    authorButton->setSelectedTextureRect(Layout::getRect(5, 0, 5, 2));
    authorButton->setPosition(Layout::toPixels(1, 6));

    const auto topBar = std::make_shared<TopBar>(getContext(), kWindowTilesX);

    mGuiContainer.pack(logo);
    mGuiContainer.pack(authorButton);
    mGuiContainer.pack(topBar);
}

void AboutState::handleInput() {
    while (const std::optional<sf::Event> event = getContext().window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            getContext().window.close();
            return;
        }
        mGuiContainer.handleEvent(*event);
    }
}

void AboutState::update() {}

void AboutState::draw() {
    getContext().window.clear(sf::Color(30, 30, 30));

    getContext().window.draw(mBackground);
    getContext().window.draw(mGuiContainer);

    getContext().window.display();
}
