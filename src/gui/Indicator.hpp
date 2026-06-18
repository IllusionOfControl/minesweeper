#ifndef MINESWEEPER_INDICATOR_HPP
#define MINESWEEPER_INDICATOR_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include "PassiveComponent.hpp"

class Indicator : public PassiveComponent {
public:
    typedef std::shared_ptr<Indicator> Ptr;

    explicit Indicator();

    ~Indicator() override;

    void setTexture(sf::Texture &texture);

    void setTextureRect(sf::IntRect rectangle);

    void setFont(const sf::Font& font);

    void setString(const sf::String& string);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
    sf::Text mText;
};

#endif //MINESWEEPER_INDICATOR_HPP
