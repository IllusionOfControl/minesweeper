#include "AssetManager.hpp"
#include <spdlog/spdlog.h>
#include <stdexcept>

void AssetManager::loadTexture(const TextureID id, std::string_view filename) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        spdlog::error("Failed to load texture '{}' from path '{}'", toString(id), filename);
        throw std::runtime_error(fmt::format("Unable to load texture: {}", filename));
    }

    spdlog::debug("Loaded texture '{}' ({}x{}) from '{}'",
                  toString(id), texture->getSize().x, texture->getSize().y, filename);

    mTextures[id] = std::move(texture);
}

void AssetManager::loadTexture(const TextureID id, std::string_view filename, const sf::IntRect& area) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename, false, area)) {
        spdlog::error("Failed to load sub-texture '{}' from path '{}'", toString(id), filename);
        throw std::runtime_error(fmt::format("Unable to load texture area from: {}", filename));
    }

    spdlog::debug("Loaded texture area '{}' from '{}'", toString(id), filename);
    mTextures[id] = std::move(texture);
}

sf::Texture& AssetManager::getTexture(const TextureID id) {
    const auto it = mTextures.find(id);
    if (it == mTextures.end()) {
        spdlog::error("Texture '{}' was requested but is not loaded!", toString(id));
        throw std::runtime_error(fmt::format("Texture not loaded: {}", toString(id)));
    }
    return *it->second;
}

const sf::Texture& AssetManager::getTexture(const TextureID id) const {
    const auto it = mTextures.find(id);
    if (it == mTextures.end()) {
        spdlog::error("Texture '{}' was requested but is not loaded!", toString(id));
        throw std::runtime_error(std::string("Texture not loaded: ") + toString(id));
    }
    return *it->second;
}

void AssetManager::loadFont(const FontID id, const std::string& fileName) {
    auto font = std::make_unique<sf::Font>();
    if (!font->openFromFile(fileName)) {
        spdlog::error("Failed to load font '{}' from path '{}'", toString(id), fileName);
        throw std::runtime_error("Unable to load font: " + fileName);
    }

    spdlog::debug("Loaded font '{}' from '{}'", toString(id), fileName);
    mFonts[id] = std::move(font);
}

sf::Font& AssetManager::getFont(const FontID id) {
    const auto it = mFonts.find(id);
    if (it == mFonts.end()) {
        spdlog::error("Font '{}' was requested but is not loaded!", toString(id));
        throw std::runtime_error(std::string("Font not loaded: ") + toString(id));
    }
    return *it->second;
}

const sf::Font& AssetManager::getFont(const FontID id) const {
    const auto it = mFonts.find(id);
    if (it == mFonts.end()) {
        spdlog::error("Font '{}' was requested but is not loaded!", toString(id));
        throw std::runtime_error(std::string("Font not loaded: ") + toString(id));
    }
    return *it->second;
}
