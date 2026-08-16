#ifndef MINESWEEPER_BUTTON_HPP
#define MINESWEEPER_BUTTON_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
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

    void select() override;

    void deselect() override;

    virtual void activate();

    void handleEvent(const sf::Event& event) override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Callback mCallback;
    sf::IntRect mNormalTextureRect;
    sf::IntRect mSelectedTextureRect;
    std::optional<sf::Sprite> mSprite;
};

#endif // MINESWEEPER_BUTTON_HPP
