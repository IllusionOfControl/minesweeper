#ifndef MINESWEEPER_BACKGROUND_HPP
#define MINESWEEPER_BACKGROUND_HPP

#include "Component.hpp"

namespace sf {
    class Sprite;
    class Texture;
    class Event;

    template<typename T>
    class Rect;
    typedef Rect<int> IntRect;
}

class Background : public Component {
public:
    typedef std::shared_ptr<Background> Ptr;

    explicit Background();

    ~Background() override;

    void setTexture(sf::Texture &texture);

    void setTextureRect(sf::IntRect rectangle);

    bool isSelected() const override;

    void select() override;

    void deselect() override;

    void handleEvent(const sf::Event &event) override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
};

#endif //MINESWEEPER_BACKGROUND_HPP
