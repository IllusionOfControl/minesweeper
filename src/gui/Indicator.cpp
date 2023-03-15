#include "Indicator.hpp"


Indicator::Indicator()
        : mSprite()
        , mText() {
    mText.setCharacterSize(20);
    mText.setStyle(sf::Text::Bold);
    mText.setScale(2.f, 2.f);
    mText.setPosition(6, -14);
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

bool Indicator::isSelected() const {
    return Component::isSelected();
}

void Indicator::select() {
    Component::select();
}

void Indicator::deselect() {
    Component::deselect();
}

void Indicator::handleEvent(const sf::Event &event) {

}


void Indicator::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}
