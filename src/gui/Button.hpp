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

    void setTexture(sf::Texture texture);

    void setNormalTextureRect(sf::IntRect rect);

    void setSelectedTextureRect(sf::IntRect rect);

//    void setPosition()

    virtual bool isSelectable() const;

    virtual void select();

    virtual void deselect();

    virtual void activate();

    virtual void deactivate();

    virtual void handleEvent(const sf::Event &event);


private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;


private:
    Callback mCallback;
    sf::Texture mTexture;
    sf::IntRect mNormalTextureRect;
    sf::IntRect mSelectedTextureRect;
    sf::Sprite mSprite;
};

#endif // MINESWEEPER_BUTTON_HPP
