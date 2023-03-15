#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <utility>
#include "Input.hpp"

Input::Input()
        : mInputFilterCallback()
        , mValidationCallback()
        , mNormalTextureRect()
        , mSelectedTextureRect()
        , mSprite()
        , mInputLimit(65536)
        , mIsValid(false) {
    // startCoord +- offset, magic numbers
    mText.setPosition(0 + 20, 32 - 10);
}

/*
 *      Callbacks
 */
void Input::setInputFilterCallback(InputFilterCallback callback) {
    mInputFilterCallback = std::move(callback);
}

void Input::setInputValidationCallback(Input::ValidationCallback callback) {
    mValidationCallback = std::move(callback);
}

/*
 *      Components
 */
void Input::setNormalTextureRect(sf::IntRect rect) {
    mNormalTextureRect = rect;
    mSprite.setTextureRect(mNormalTextureRect);
}

void Input::setSelectedTextureRect(sf::IntRect rect) {
    mSelectedTextureRect = rect;
}

/*
 *      Sprite
 */

void Input::setTexture(const sf::Texture& texture) {
    mSprite.setTexture(texture);
}

void Input::select() {
    Component::select();
    mSprite.setTextureRect(mSelectedTextureRect);
}

void Input::deselect() {
    Component::deselect();
    mSprite.setTextureRect(mNormalTextureRect);
}

void Input::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}

/*
 *      Text
 */

void Input::setFont(const sf::Font &font) {
    mText.setFont(font);
}

void Input::setStyle(sf::Text::Style style) {
    mText.setStyle(style);
}

void Input::setCharacterSize(unsigned int size) {
    mText.setCharacterSize(size);
}

void Input::setFillColor(sf::Color color) {
    mText.setFillColor(color);
}

sf::String Input::getString() const {
    return mText.getString();
}

void Input::setInputLimit(int numberOfCharacters) {
    mInputLimit = numberOfCharacters;
}

void Input::setValid() {
    mIsValid = true;
    mText.setFillColor(sf::Color::Green);
}

void Input::setInvalid() {
    mIsValid = false;
    mText.setFillColor(sf::Color::Red);
}

bool Input::isValid() const {
    return mIsValid;
}

void Input::handleEvent(const sf::Event &event) {
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
        case sf::Event::TextEntered: {
            if (isSelected()) {
                sf::Uint32 unicode = event.text.unicode;
                sf::String string = mText.getString();

                if (unicode == '\b' && string.getSize() > 0)
                    string.erase(string.getSize() - 1, 1);
                if (filterInput(unicode) && string.getSize() < mInputLimit)
                    string += unicode;

                if (validateInput(string))
                    setValid();
                else
                    setInvalid();

                mText.setString(string);
            }

            break;
        }
        default:
            break;
    }
}

bool Input::filterInput(sf::Uint32 unicode) {
    if (mInputFilterCallback)
        return mInputFilterCallback(unicode);
    return true;
}

bool Input::validateInput(const sf::String& string) {
    if (string.getSize() == 0)
        return false;

    if (mValidationCallback)
        return mValidationCallback(string);

    return true;
}
