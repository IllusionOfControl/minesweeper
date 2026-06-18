#include "AssetManager.hpp"
#include <stdexcept>

void AssetManager::loadTexture(std::string name, std::string fileName)
{
    sf::Texture tex;

    if (!tex.loadFromFile(fileName))
        throw std::runtime_error("Unable to load texture '" + name + "' from " + fileName);

    this->mTextures[name] = tex;
}

void AssetManager::loadTexture(std::string name, std::string fileName, sf::IntRect area)
{
    sf::Texture tex;

    if (!tex.loadFromFile(fileName, area))
        throw std::runtime_error("Unable to load texture '" + name + "' from " + fileName);

    this->mTextures[name] = tex;
}

sf::Texture &AssetManager::getTexture(std::string name)
{
    auto it = this->mTextures.find(name);
    if (it == this->mTextures.end())
        throw std::runtime_error("Texture not loaded: '" + name + "'");

    return it->second;
}

void AssetManager::loadFont(std::string name, std::string fileName)
{
    sf::Font font;

    if (!font.loadFromFile(fileName))
        throw std::runtime_error("Unable to load font '" + name + "' from " + fileName);

    this->mFonts[name] = font;
}

sf::Font &AssetManager::getFont(std::string name)
{
    auto it = this->mFonts.find(name);
    if (it == this->mFonts.end())
        throw std::runtime_error("Font not loaded: '" + name + "'");

    return it->second;
}
