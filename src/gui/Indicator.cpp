#include "Indicator.hpp"

namespace {
    constexpr unsigned int kCharacterSize = 20;
    constexpr float kTextScale = 2.f;
    // Offset of the digits over the LED background.
    constexpr float kTextOffsetX = 6.f;
    constexpr float kTextOffsetY = -14.f;
}

Indicator::Indicator()
        : mSprite()
        , mText() {
    mText.setCharacterSize(kCharacterSize);
    mText.setStyle(sf::Text::Bold);
    mText.setScale(kTextScale, kTextScale);
    mText.setPosition(kTextOffsetX, kTextOffsetY);
}

Indicator::~Indicator() = default;

void Indicator::setTexture(sf::Texture &texture) {
    texture.setRepeated(true);
    mSprite.setTexture(texture);
}

void Indicator::setTextureRect(sf::IntRect rectangle) {
    mSprite.setTextureRect(rectangle);
}

void Indicator::setFont(const sf::Font& font) {
    mText.setFont(font);
}

void Indicator::setString(const sf::String& string) {
    mText.setString(string);
}

void Indicator::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}
