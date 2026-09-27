#ifndef MINESWEEPER_LAYOUT_HPP
#define MINESWEEPER_LAYOUT_HPP

#include <SFML/System/Vector2.hpp>

namespace Layout {
    inline constexpr int TileSize = 32;

    [[nodiscard]] constexpr sf::Vector2u toWindowSize(const int tilesX, const int tilesY) noexcept {
        return {
            static_cast<unsigned int>(tilesX * TileSize),
            static_cast<unsigned int>(tilesY * TileSize)
        };
    }

    [[nodiscard]] constexpr sf::Vector2f toPixels(const int tileX, const int tileY) noexcept {
        return {
            static_cast<float>(tileX * TileSize),
            static_cast<float>(tileY * TileSize)
        };
    }

    [[nodiscard]] constexpr sf::IntRect getRect(const int tileX, const int tileY, const int widthTiles = 1,
                                                const int heightTiles = 1) noexcept {
        return {
            {tileX * TileSize, tileY * TileSize},
            {widthTiles * TileSize, heightTiles * TileSize}
        };
    }
}

#endif // MINESWEEPER_LAYOUT_HPP
