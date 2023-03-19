#ifndef MINESWEEPER_ASSETMANAGER_HPP
#define MINESWEEPER_ASSETMANAGER_HPP

#include <map>

#include <SFML/Graphics.hpp>

class AssetManager {
public:
    AssetManager() { }
    ~AssetManager() { }

    void loadTexture(std::string name, std::string fileName);
    void loadTexture(std::string name, std::string fileName, sf::IntRect area);
    sf::Texture &getTexture(std::string name);

    void LoadFont(std::string name, std::string fileName);
    sf::Font &GetFont(std::string name);

private:
    std::map<std::string, sf::Texture> mTextures;
    std::map<std::string, sf::Font> mFonts;
};


#endif //MINESWEEPER_ASSETMANAGER_HPP
