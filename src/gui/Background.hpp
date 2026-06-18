#ifndef MINESWEEPER_BACKGROUND_HPP
#define MINESWEEPER_BACKGROUND_HPP

#include "PassiveComponent.hpp"

namespace sf {
    class Sprite;
    class Texture;

    template<typename T>
    class Rect;
    typedef Rect<int> IntRect;
}

class Background : public PassiveComponent {
public:
    typedef std::shared_ptr<Background> Ptr;

    explicit Background();

    ~Background() override;

    void setTexture(sf::Texture &texture);

    void setTextureRect(sf::IntRect rectangle);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
};

#endif //MINESWEEPER_BACKGROUND_HPP
