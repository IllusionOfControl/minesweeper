#include "SmileButton.hpp"
#include "Layout.hpp"

namespace {
    constexpr sf::IntRect getSmallSmileRect(const int index) noexcept {
        return Layout::getRect(index, 0, 1, 1);
    }

    constexpr sf::IntRect getLargeSmileRect(const int index) noexcept {
        return {
            {(index * 2 + 5) * Layout::TileSize, 0},
            {2 * Layout::TileSize, Layout::TileSize}
        };
    }
}

SmileButton::SmileButton(const bool isSmall)
    : mReaction(SmileUsual)
    , mIsSmall(isSmall) {
    updateTexture();
}

void SmileButton::setReaction(const SmileReaction reaction) {
    mReaction = reaction;
    updateTexture();
}

SmileButton::SmileReaction SmileButton::getReaction() const noexcept {
    return mReaction;
}

bool SmileButton::isSmall() const noexcept {
    return mIsSmall;
}

void SmileButton::updateTexture() {
    if (mIsSmall) {
        setTextureRect(getSmallSmileRect(mReaction));
    } else {
        setTextureRect(getLargeSmileRect(mReaction));
    }
}
