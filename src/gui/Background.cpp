#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include "Background.hpp"


Background::Background()
        : mSprite() {

}

Background::~Background() = default;

void Background::setTexture(sf::Texture &texture) {
    texture.setRepeated(true);
    mSprite.setTexture(texture);
}

void Background::setTextureRect(sf::IntRect rectangle) {
    mSprite.setTextureRect(rectangle);
}

bool Background::isSelected() const {
    return Component::isSelected();
}

void Background::select() {
    Component::select();
}

void Background::deselect() {
    Component::deselect();
}

void Background::handleEvent(const sf::Event &event) {

}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}
