#ifndef MINESWEEPER_INDICATOR_HPP
#define MINESWEEPER_INDICATOR_HPP

#include <memory>
#include <optional>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "PassiveComponent.hpp"
#include "Text.hpp"

class Indicator : public PassiveComponent {
public:
    using Ptr = std::shared_ptr<Indicator>;

    Indicator();
    ~Indicator() override = default;

    void setTexture(const sf::Texture& texture);
    void setTextureRect(sf::IntRect rectangle);
    void setFont(const sf::Font& font);
    void setString(const sf::String& string);
    const sf::String& getString() const noexcept;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::IntRect mTextureRect{};
    std::optional<sf::Sprite> mSprite;
    Text mText;
};

#endif // MINESWEEPER_INDICATOR_HPP
