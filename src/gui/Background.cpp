#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include "Background.hpp"


void Background::setTexture(const sf::Texture &texture) {
    mSprite.emplace(texture);
}

void Background::setTextureRect(const sf::IntRect rectangle) {
    if (mSprite) mSprite->setTextureRect(rectangle);
}

void Background::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    if (mSprite) target.draw(mSprite.value(), states);
}
