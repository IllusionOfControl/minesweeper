#ifndef MINESWEEPER_INPUT_HPP
#define MINESWEEPER_INPUT_HPP

#include <memory>
#include <functional>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <regex>
#include "Component.hpp"

class Input : public Component {
public:
    typedef std::shared_ptr<Input> Ptr;
    typedef std::function<bool(const sf::Uint32)> InputFilterCallback;
    typedef std::function<bool(const sf::String)> ValidationCallback;

public:
    Input();

    void setInputFilterCallback(InputFilterCallback callback);
    void setInputValidationCallback(ValidationCallback callback);

    // Sprite proxy
    void setTexture(const sf::Texture& texture);
    void setNormalTextureRect(sf::IntRect rect);
    void setSelectedTextureRect(sf::IntRect rect);

    //Text proxy
    void setFont(const sf::Font &font);
    void setStyle(sf::Text::Style style);
    void setCharacterSize(unsigned int size);
    void setFillColor(sf::Color);
    sf::String getString() const;

    void setInputLimit(int numberOfCharacters);
    void setValid();
    void setInvalid();
    bool isValid() const;

    // component
    void handleEvent(const sf::Event &event) override;
    void select() override;
    void deselect() override;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    bool filterInput(sf::Uint32 unicode);
    bool validateInput(const sf::String& string);

private:
    InputFilterCallback mInputFilterCallback;
    ValidationCallback mValidationCallback;
    sf::IntRect mNormalTextureRect;
    sf::IntRect mSelectedTextureRect;
    sf::Sprite mSprite;
    sf::Text mText;

    bool mIsValid;
    int mInputLimit;
};
#endif //MINESWEEPER_INPUT_HPP
