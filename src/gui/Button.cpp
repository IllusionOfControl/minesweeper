#include "Button.hpp"

#include <cmath>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

void Button::setCallback(Callback callback) { mCallback = std::move(callback); }

void Button::setTexture(const sf::Texture& texture) {
    if (mSprite.has_value()) {
        mSprite->setTexture(texture, false);
    } else {
        mSprite.emplace(texture);
        if (mNormalTextureRect != sf::IntRect{}) {
            mSprite->setTextureRect(isSelected() ? mSelectedTextureRect : mNormalTextureRect);
        }
    }
    updateTextLayout();
}

void Button::setTextureRect(const sf::IntRect rect) {
    setNormalTextureRect(rect);
    setSelectedTextureRect(rect);
}

void Button::setNormalTextureRect(const sf::IntRect rect) {
    mNormalTextureRect = rect;
    if (mSprite.has_value()) {
        mSprite->setTextureRect(isSelected() ? mSelectedTextureRect : mNormalTextureRect);
        updateTextLayout();
    }
}

void Button::setSelectedTextureRect(const sf::IntRect rect) {
    mSelectedTextureRect = rect;
    if (mSprite.has_value() && isSelected()) {
        mSprite->setTextureRect(mSelectedTextureRect);
        updateTextLayout();
    }
}

void Button::setText(const sf::Font& font, const sf::String& string, const unsigned int characterSize,
                     const sf::Color normalColor, const sf::Color selectedColor) {
    mNormalTextColor = normalColor;
    mSelectedTextColor = selectedColor;
    mText.emplace(font, string, characterSize);
    mText->setStyle(sf::Text::Bold);
    mText->setFillColor(isSelected() ? mSelectedTextColor : mNormalTextColor);
    updateTextLayout();
}

void Button::updateTextLayout() {
    if (!mText.has_value() || !mSprite.has_value()) return;

    const auto tb = mText->getLocalBounds();
    const auto sb = mSprite->getLocalBounds();
    mText->setOrigin({std::round(tb.position.x + tb.size.x / 2.f), std::round(tb.position.y + tb.size.y / 2.f)});
    mText->setPosition({std::round(sb.size.x / 2.f), std::round(sb.size.y / 2.f)});
}

void Button::select() {
    Component::select();
    if (mSprite.has_value()) mSprite->setTextureRect(mSelectedTextureRect);
    if (mText.has_value()) mText->setFillColor(mSelectedTextColor);
}

void Button::deselect() {
    Component::deselect();
    if (mSprite.has_value()) mSprite->setTextureRect(mNormalTextureRect);
    if (mText.has_value()) mText->setFillColor(mNormalTextColor);
}

void Button::activate() {
    if (mCallback)
        mCallback();
}

void Button::handleEvent(const sf::Event& event) {
    if (!mSprite.has_value()) return;

    const sf::Rect<float> spriteBounds = mSprite->getLocalBounds();
    const sf::Rect<float> globalBounds = getTransform().transformRect(spriteBounds);

    if (const auto* moved = event.getIf<sf::Event::MouseMoved>()) {
        if (const auto mousePos = sf::Vector2f(static_cast<float>(moved->position.x),
                                               static_cast<float>(moved->position.y)); globalBounds.contains(mousePos))
            select();
        else
            deselect();
    }
    if (event.is<sf::Event::MouseButtonPressed>()) { if (isSelected()) activate(); }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    if (mSprite.has_value()) {
        target.draw(*mSprite, states);
    }
    if (mText.has_value()) {
        target.draw(*mText, states);
    }
}