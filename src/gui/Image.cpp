#include "Image.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

void Image::setTexture(sf::Texture &texture) {
    if (!mSprite.has_value()) mSprite.emplace(texture);
    else mSprite->setTexture(texture);
}

void Image::setTextureRect(const sf::IntRect rectangle) {
    if (mSprite.has_value()) mSprite->setTextureRect(rectangle);
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    if (mSprite.has_value()) target.draw(*mSprite, states);
}
