#include "Indicator.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace {
    constexpr unsigned int kCharacterSize = 20;
    constexpr float kTextScale = 2.f;
    constexpr float kTextOffsetX = 6.f;
    constexpr float kTextOffsetY = -14.f;
}

Indicator::Indicator() {
    mText.setCharacterSize(kCharacterSize);
    mText.setStyle(sf::Text::Bold);
    mText.setFillColor(sf::Color::Red);
    mText.setScale({kTextScale, kTextScale});
    mText.setPosition({kTextOffsetX, kTextOffsetY});
}

void Indicator::setTexture(const sf::Texture& texture) {
    const_cast<sf::Texture&>(texture).setRepeated(true);
    if (mSprite.has_value()) {
        mSprite->setTexture(texture, false);
    } else {
        mSprite.emplace(texture);
        if (mTextureRect != sf::IntRect{}) {
            mSprite->setTextureRect(mTextureRect);
        }
    }
}

void Indicator::setTextureRect(const sf::IntRect rectangle) {
    mTextureRect = rectangle;
    if (mSprite.has_value()) {
        mSprite->setTextureRect(mTextureRect);
    }
}

void Indicator::setFont(const sf::Font& font) {
    mText.setFont(font);
}

void Indicator::setString(const sf::String& string) {
    mText.setString(string);
}

const sf::String& Indicator::getString() const noexcept {
    return mText.getString();
}

void Indicator::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    if (mSprite.has_value()) {
        target.draw(*mSprite, states);
    }
    target.draw(mText, states);
}
