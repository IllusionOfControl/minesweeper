#ifndef MINESWEEPER_IMAGE_HPP
#define MINESWEEPER_IMAGE_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "PassiveComponent.hpp"

class Image : public PassiveComponent {
public:
    using Ptr = std::shared_ptr<Image>;

    Image() = default;

    void setTexture(const sf::Texture &texture);

    void setTextureRect(sf::IntRect rectangle);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    std::optional<sf::Sprite> mSprite;
};

#endif //MINESWEEPER_IMAGE_HPP