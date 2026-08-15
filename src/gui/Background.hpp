#ifndef MINESWEEPER_BACKGROUND_HPP
#define MINESWEEPER_BACKGROUND_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "PassiveComponent.hpp"

class Background : public PassiveComponent {
public:
    typedef std::shared_ptr<Background> Ptr;

    Background() = default;

    void setTexture(sf::Texture &texture);

    void setTextureRect(sf::IntRect rectangle);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    std::optional<sf::Sprite> mSprite;
};

#endif //MINESWEEPER_BACKGROUND_HPP
