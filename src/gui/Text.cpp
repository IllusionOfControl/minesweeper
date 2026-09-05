#include "Text.hpp"

#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Text::Text(const sf::Font& font, const sf::String& string = "", const unsigned int characterSize = 20)
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

const sf::String& Text::getString() const noexcept { return mText.getString(); }

sf::FloatRect Text::getLocalBounds() const { return mText.getLocalBounds(); }

void Text::alignInBounds(const sf::IntRect& bounds, const AlignH hAlign, const AlignV vAlign,
                         const sf::Vector2f offset) {
    const sf::FloatRect textBounds = mText.getLocalBounds();
    sf::Vector2f origin{0.f, 0.f};
    sf::Vector2f pos{0.f, 0.f};

    const auto bx = static_cast<float>(bounds.position.x);
    const auto by = static_cast<float>(bounds.position.y);
    const auto bw = static_cast<float>(bounds.size.x);
    const auto bh = static_cast<float>(bounds.size.y);

    switch (hAlign) {
    case AlignH::Left: origin.x = textBounds.position.x;
        pos.x = bx + offset.x;
        break;
    case AlignH::Center: origin.x = std::round(textBounds.position.x + textBounds.size.x / 2.f);
        pos.x = std::round(bx + bw / 2.f + offset.x);
        break;
    case AlignH::Right: origin.x = textBounds.position.x + textBounds.size.x;
        pos.x = bx + bw - offset.x;
        break;
    }

    switch (vAlign) {
    case AlignV::Top: origin.y = textBounds.position.y;
        pos.y = by + offset.y;
        break;
    case AlignV::Center: origin.y = std::round(textBounds.position.y + textBounds.size.y / 2.f);
        pos.y = std::round(by + bh / 2.f + offset.y);
        break;
    case AlignV::Bottom: origin.y = textBounds.position.y + textBounds.size.y;
        pos.y = by + bh - offset.y;
        break;
    }

    setOrigin(origin);
    setPosition(pos);
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mText, states);
}
