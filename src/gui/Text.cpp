#include "Text.hpp"

#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Text::Text(const sf::Font& font, const sf::String& string, const unsigned int characterSize)
    : mText(font, string, characterSize) {}

void Text::setFont(const sf::Font& font) { mText.setFont(font); }

void Text::setString(const sf::String& string) { mText.setString(string); }

void Text::setString(std::string_view utf8String) {
    mText.setString(sf::String::fromUtf8(utf8String.begin(), utf8String.end()));
}

void Text::setCharacterSize(const unsigned int size) { mText.setCharacterSize(size); }

void Text::setStyle(const sf::Text::Style style) { mText.setStyle(style); }

void Text::setFillColor(const sf::Color color) { mText.setFillColor(color); }

void Text::setOutlineColor(const sf::Color color) { mText.setOutlineColor(color); }

void Text::setOutlineThickness(const float thickness) { mText.setOutlineThickness(thickness); }

void Text::setTextRect(const sf::IntRect& rectangle) { mTextRect = rectangle; }

const sf::IntRect& Text::getTextRect() const noexcept { return mTextRect; }

const sf::String& Text::getString() const noexcept { return mText.getString(); }

sf::FloatRect Text::getLocalBounds() const { return mText.getLocalBounds(); }

void Text::alignHorizontal(const AlignH align, const float offsetX) {
    const auto textBounds = mText.getLocalBounds();
    const auto bx = static_cast<float>(mTextRect.position.x);
    const auto bw = static_cast<float>(mTextRect.size.x);

    float originX = 0.f;
    float posX = 0.f;

    switch (align) {
        case AlignH::Left:
            originX = textBounds.position.x;
            posX = bx + offsetX;
            break;
        case AlignH::Center:
            originX = std::round(textBounds.position.x + textBounds.size.x / 2.f);
            posX = std::round(bx + bw / 2.f + offsetX);
            break;
        case AlignH::Right:
            originX = textBounds.position.x + textBounds.size.x;
            posX = bx + bw - offsetX;
            break;
    }

    setOrigin({originX, getOrigin().y});
    setPosition({posX, getPosition().y});
}

void Text::alignVertical(const AlignV align, const float offsetY) {
    const auto textBounds = mText.getLocalBounds();
    const auto by = static_cast<float>(mTextRect.position.y);
    const auto bh = static_cast<float>(mTextRect.size.y);

    float originY = 0.f;
    float posY = 0.f;

    switch (align) {
        case AlignV::Top:
            originY = textBounds.position.y;
            posY = by + offsetY;
            break;
        case AlignV::Center:
            originY = std::round(textBounds.position.y + textBounds.size.y / 2.f);
            posY = std::round(by + bh / 2.f + offsetY);
            break;
        case AlignV::Bottom:
            originY = textBounds.position.y + textBounds.size.y;
            posY = by + bh - offsetY;
            break;
    }

    setOrigin({getOrigin().x, originY});
    setPosition({getPosition().x, posY});
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mText, states);
}
