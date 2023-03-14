#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Button.hpp"

Button::Button()
        : mCallback()
        , mTexture()
        , mNormalTextureRect()
        , mSelectedTextureRect()
        , mSprite() {
}

void Button::setCallback(Callback callback) {
    mCallback = std::move(callback);
}

void Button::setTexture(sf::Texture texture) {
    mTexture = texture;
    mSprite.setTexture(mTexture);
}

void Button::setNormalTextureRect(sf::IntRect rect) {
    mNormalTextureRect = rect;
    mSprite.setTextureRect(mNormalTextureRect);
}

void Button::setSelectedTextureRect(sf::IntRect rect) {
    mSelectedTextureRect = rect;
}

void Button::select() {
    Component::select();
    mSprite.setTextureRect(mSelectedTextureRect);
}

void Button::deselect() {
    Component::deselect();
    mSprite.setTextureRect(mNormalTextureRect);
}

void Button::activate() {
     if (mCallback)
        mCallback();
}

void Button::handleEvent(const sf::Event &event) {
    sf::Rect<float> spriteBounds = mSprite.getLocalBounds();
    sf::Rect<float> globalBounds = getTransform().transformRect(spriteBounds);
    switch (event.type) {
        case sf::Event::MouseMoved: {
            auto mousePos = sf::Vector2f((float) event.mouseMove.x, (float) event.mouseMove.y);
            if (globalBounds.contains(mousePos))
                select();
            else
                deselect();

            break;
        }

        case sf::Event::MouseButtonReleased: {
            if (isSelected()) activate();
            break;
        }
        default:
            break;
    }
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
