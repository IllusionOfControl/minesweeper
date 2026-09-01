#ifndef MINESWEEPER_TOPBAR_HPP
#define MINESWEEPER_TOPBAR_HPP

#include "Container.hpp"
#include "Button.hpp"
#include "GameContext.hpp"
#include "Layout.hpp"
#include "managers/ResourceIdentifiers.hpp"

class TopBar : public Container {
public:
    using Ptr = std::shared_ptr<TopBar>;

    TopBar(GameContext& context, int contentWidthInTiles, bool showBackButton = true) {
        const auto& texture = context.assets.getTexture(TextureID::TopBarButtons);

        if (showBackButton) {
            auto menuButton = std::make_shared<Button>();
            menuButton->setTexture(texture);
            menuButton->setNormalTextureRect(Layout::getRect(0, 0));
            menuButton->setSelectedTextureRect(Layout::getRect(1, 0));
            menuButton->setPosition(Layout::toPixels(0, 0));
            menuButton->setCallback([&context]() { context.states.changeState(StateID::MainMenu); });
            pack(menuButton);
        }

        auto exitButton = std::make_shared<Button>();
        exitButton->setTexture(texture);
        exitButton->setNormalTextureRect(Layout::getRect(0, 1));
        exitButton->setSelectedTextureRect(Layout::getRect(1, 1));

        exitButton->setPosition(Layout::toPixels(contentWidthInTiles - 1, 0));
        exitButton->setCallback([&context]() { context.window.close(); });
        pack(exitButton);
    }
};

#endif // MINESWEEPER_TOPBAR_HPP
