#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Button.hpp"

#include <spdlog/spdlog.h>

void Button::setCallback(Callback callback) { mCallback = std::move(callback); }

void Button::setTexture(const sf::Texture& texture) {
    if (mSprite.has_value()) mSprite->setTexture(texture, false);
    else mSprite.emplace(texture);
}

void Button::setTextureRect(const sf::IntRect rect) {
    setNormalTextureRect(rect);
    setSelectedTextureRect(rect);
}

void Button::setNormalTextureRect(const sf::IntRect rect) {
    mNormalTextureRect = rect;
    if (mSprite.has_value()) mSprite->setTextureRect(mNormalTextureRect);
}

void Button::setSelectedTextureRect(const sf::IntRect rect) { mSelectedTextureRect = rect; }

void Button::select() {
    Component::select();
    if (mSprite.has_value()) mSprite->setTextureRect(mSelectedTextureRect);
}

void Button::deselect() {
    Component::deselect();
    if (mSprite.has_value()) mSprite->setTextureRect(mNormalTextureRect);
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
    if (!mSprite.has_value()) return;

    states.transform *= getTransform();
    target.draw(*mSprite, states);
}
