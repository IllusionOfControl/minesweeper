#ifndef MINESWEEPER_INPUT_HPP
#define MINESWEEPER_INPUT_HPP

#include <functional>
#include <memory>
#include <optional>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

#include "Component.hpp"
#include "Text.hpp"

class Input : public Component {
public:
    using Ptr = std::shared_ptr<Input>;
    using InputFilterCallback = std::function<bool(char32_t)>;
    using ValidationCallback = std::function<bool(const sf::String&)>;

    Input();
    explicit Input(const sf::Font& font);
    ~Input() override = default;

    void setInputFilterCallback(InputFilterCallback callback);
    void setInputValidationCallback(ValidationCallback callback);

    void setTexture(const sf::Texture& texture);
    void setTextureRect(sf::IntRect rect);
    void setNormalTextureRect(sf::IntRect rect);
    void setSelectedTextureRect(sf::IntRect rect);

    void setFont(const sf::Font& font);
    void setStyle(sf::Text::Style style);
    void setCharacterSize(unsigned int size);
    void setFillColor(sf::Color color);

    void setString(const sf::String& string);
    const sf::String& getString() const;

    Text& getText() noexcept;
    const Text& getText() const noexcept;

    void setInputLimit(int numberOfCharacters);
    void setValid();
    void setInvalid();
    bool isValid() const;

    void select() override;
    void deselect() override;
    void handleEvent(const sf::Event& event) override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool filterInput(char32_t unicode) const;
    bool validateInput(const sf::String& string) const;
    void updateDisplayedText();

    InputFilterCallback mInputFilterCallback;
    ValidationCallback mValidationCallback;

    sf::IntRect mNormalTextureRect{};
    sf::IntRect mSelectedTextureRect{};

    std::optional<sf::Sprite> mSprite;
    Text mText;
    sf::String mValue;

    bool mIsValid = false;
    int mInputLimit = 65536;
};

#endif // MINESWEEPER_INPUT_HPP
