#ifndef MINESWEEPER_BUTTON_HPP
#define MINESWEEPER_BUTTON_HPP

#include "Component.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>

class Button : public Component {
public:
    typedef std::shared_ptr<Button> Ptr;
    typedef std::function<void()> Callback;

public:
    Button();

    void setCallback(Callback callback);

    void setTexture(const sf::Texture& texture);

    void setTextureRect(sf::IntRect rect);

    void setNormalTextureRect(sf::IntRect rect);

    void setSelectedTextureRect(sf::IntRect rect);

    void select() override;

    void deselect() override;

    virtual void activate();

    void handleEvent(const sf::Event &event) override;


private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


private:
    Callback mCallback;
    sf::IntRect mNormalTextureRect;
    sf::IntRect mSelectedTextureRect;
    sf::Sprite mSprite;
};

#endif // MINESWEEPER_BUTTON_HPP
