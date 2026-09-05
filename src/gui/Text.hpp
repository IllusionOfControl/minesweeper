#ifndef MINESWEEPER_TEXT_HPP
#define MINESWEEPER_TEXT_HPP

#include <memory>
#include <string>
#include <string_view>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "PassiveComponent.hpp"

class Text : public PassiveComponent {
public:
    using Ptr = std::shared_ptr<Text>;

    enum class AlignH { Left, Center, Right };
    enum class AlignV { Top, Center, Bottom };

    explicit Text(const sf::Font&, const sf::String&, unsigned int);
    ~Text() override = default;

    void setFont(const sf::Font& font);
    void setString(const sf::String& string);
    void setString(std::string_view utf8String);
    void setCharacterSize(unsigned int size);
    void setStyle(sf::Text::Style style);
    void setFillColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setOutlineThickness(float thickness);

    const sf::String& getString() const noexcept;
    sf::FloatRect getLocalBounds() const;

    void alignInBounds(const sf::IntRect& bounds,
                       AlignH hAlign = AlignH::Left,
                       AlignV vAlign = AlignV::Center,
                       sf::Vector2f offset = {0.f, 0.f});

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Text mText;
};

#endif // MINESWEEPER_TEXT_HPP