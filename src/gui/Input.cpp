#include "Input.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <utility>

namespace {
    constexpr float kTextOffsetX = 20.f;
    constexpr float kTextOffsetY = 22.f;
}

Input::Input() {
    mText.setPosition({kTextOffsetX, kTextOffsetY});
}

Input::Input(const sf::Font& font)
    : mText(font) {
    mText.setPosition({kTextOffsetX, kTextOffsetY});
}

void Input::setInputFilterCallback(InputFilterCallback callback) {
    mInputFilterCallback = std::move(callback);
}

void Input::setInputValidationCallback(ValidationCallback callback) {
    mValidationCallback = std::move(callback);
}

void Input::setTexture(const sf::Texture& texture) {
    if (mSprite.has_value()) {
        mSprite->setTexture(texture, false);
    } else {
        mSprite.emplace(texture);
    }
}

void Input::setTextureRect(const sf::IntRect rect) {
    setNormalTextureRect(rect);
    setSelectedTextureRect(rect);
}

void Input::setNormalTextureRect(const sf::IntRect rect) {
    mNormalTextureRect = rect;
    mText.setTextRect(mNormalTextureRect);
    if (mSprite.has_value() && !isSelected()) {
        mSprite->setTextureRect(mNormalTextureRect);
    }
}

void Input::setSelectedTextureRect(const sf::IntRect rect) {
    mSelectedTextureRect = rect;
    if (mSprite.has_value() && isSelected()) {
        mSprite->setTextureRect(mSelectedTextureRect);
    }
}

void Input::select() {
    Component::select();
    if (mSprite.has_value()) {
        mSprite->setTextureRect(mSelectedTextureRect);
    }
    updateDisplayedText();
}

void Input::deselect() {
    Component::deselect();
    if (mSprite.has_value()) {
        mSprite->setTextureRect(mNormalTextureRect);
    }
    updateDisplayedText();
}

void Input::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    if (mSprite.has_value()) {
        target.draw(*mSprite, states);
    }
    target.draw(mText, states);
}

void Input::setFont(const sf::Font& font) {
    mText.setFont(font);
}

void Input::setStyle(const sf::Text::Style style) {
    mText.setStyle(style);
}

void Input::setCharacterSize(const unsigned int size) {
    mText.setCharacterSize(size);
}

void Input::setFillColor(const sf::Color color) {
    mText.setFillColor(color);
}

void Input::setString(const sf::String& string) {
    mValue = string;
    if (validateInput(mValue)) {
        setValid();
    } else {
        setInvalid();
    }
    updateDisplayedText();
}

const sf::String& Input::getString() const {
    return mValue;
}

Text& Input::getText() noexcept {
    return mText;
}

const Text& Input::getText() const noexcept {
    return mText;
}

void Input::setInputLimit(const int numberOfCharacters) {
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

void Input::updateDisplayedText() {
    if (isSelected()) {
        mText.setString(mValue + "_");
    } else {
        mText.setString(mValue);
    }
}

void Input::handleEvent(const sf::Event& event) {
    if (!mSprite.has_value()) {
        return;
    }

    const sf::FloatRect spriteBounds = mSprite->getLocalBounds();
    const sf::FloatRect globalBounds = getTransform().transformRect(spriteBounds);

    if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
        const auto mousePos = sf::Vector2f(static_cast<float>(mouseMoved->position.x),
                                           static_cast<float>(mouseMoved->position.y));
        if (globalBounds.contains(mousePos)) {
            select();
        } else {
            deselect();
        }
    } else if (const auto* textEntered = event.getIf<sf::Event::TextEntered>()) {
        if (isSelected()) {
            const char32_t unicode = textEntered->unicode;

            if (unicode == U'\b' && !mValue.isEmpty()) {
                mValue.erase(mValue.getSize() - 1, 1);
            } else if (filterInput(unicode) && static_cast<int>(mValue.getSize()) < mInputLimit) {
                mValue += unicode;
            }

            if (validateInput(mValue)) {
                setValid();
            } else {
                setInvalid();
            }

            updateDisplayedText();
        }
    }
}

bool Input::filterInput(const char32_t unicode) const {
    if (mInputFilterCallback) {
        return mInputFilterCallback(unicode);
    }
    return true;
}

bool Input::validateInput(const sf::String& string) const {
    if (string.isEmpty()) {
        return false;
    }

    if (mValidationCallback) {
        return mValidationCallback(string);
    }

    return true;
}
