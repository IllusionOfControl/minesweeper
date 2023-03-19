#include "AssetManager.hpp"
#include <iostream>

void AssetManager::loadTexture(std::string name, std::string fileName)
{
    sf::Texture tex;

    if (tex.loadFromFile(fileName))
    {
        this->mTextures[name] = tex;
    } else {
        std::cout << "Unable to load texture on the path " + fileName << std::endl;
    }
}

void AssetManager::loadTexture(std::string name, std::string fileName, sf::IntRect area)
{
    sf::Texture tex;

    if (tex.loadFromFile(fileName, area))
    {
        this->mTextures[name] = tex;
    }
}

sf::Texture &AssetManager::getTexture(std::string name)
{
    return this->mTextures.at(name);
}

void AssetManager::LoadFont(std::string name, std::string fileName)
{
    sf::Font font;

    if (font.loadFromFile(fileName))
    {
        this->mFonts[name] = font;
    }
}

sf::Font &AssetManager::GetFont(std::string name)
{
    return this->mFonts.at(name);
}