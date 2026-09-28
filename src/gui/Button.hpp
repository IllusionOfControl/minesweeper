#ifndef MINESWEEPER_BUTTON_HPP
#define MINESWEEPER_BUTTON_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <optional>
#include <functional>

#include "Component.hpp"

class Button : public Component {
public:
    using Ptr = std::shared_ptr<Button>;
    using Callback = std::function<void()>;

    Button() = default;

    void setCallback(Callback callback);

    void setTexture(const sf::Texture& texture);

    void setTextureRect(sf::IntRect rect);

    void setNormalTextureRect(sf::IntRect rect);

    void setSelectedTextureRect(sf::IntRect rect);

    void setText(const sf::Font& font, const sf::String& string, unsigned int characterSize = 20,
                 sf::Color normalColor = sf::Color::White, sf::Color selectedColor = sf::Color::Yellow);

    void select() override;

    void deselect() override;

    virtual void activate();

    void handleEvent(const sf::Event& event) override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateTextLayout();

    Callback mCallback;
    sf::IntRect mNormalTextureRect;
    sf::IntRect mSelectedTextureRect;
    std::optional<sf::Sprite> mSprite;

    std::optional<sf::Text> mText;
    sf::Color mNormalTextColor{sf::Color::White};
    sf::Color mSelectedTextColor{sf::Color::Yellow};
};

#endif // MINESWEEPER_BUTTON_HPP