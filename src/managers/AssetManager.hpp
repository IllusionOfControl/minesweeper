#ifndef MINESWEEPER_ASSETMANAGER_HPP
#define MINESWEEPER_ASSETMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.hpp"

class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    void loadTexture(TextureID id, std::string_view filename);
    void loadTexture(TextureID id, std::string_view filename, const sf::IntRect& area);
    sf::Texture& getTexture(TextureID id);
    [[nodiscard]] const sf::Texture& getTexture(TextureID id) const;

    void loadFont(FontID id, const std::string& fileName);
    sf::Font& getFont(FontID id);
    [[nodiscard]] const sf::Font& getFont(FontID id) const;


private:
    std::unordered_map<TextureID, std::unique_ptr<sf::Texture>> mTextures;
    std::unordered_map<FontID, std::unique_ptr<sf::Font>> mFonts;
};


#endif //MINESWEEPER_ASSETMANAGER_HPP
