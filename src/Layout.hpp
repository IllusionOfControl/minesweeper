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

// namespace Board {
//     inline constexpr int BorderTop = 4;     // Место под верхнюю панель
//     inline constexpr int BorderBottom = 1;
//     inline constexpr int BorderLeft = 1;
//     inline constexpr int BorderRight = 1;
//
//     [[nodiscard]] constexpr sf::Vector2u calculateWindowSize(int width, int height) noexcept {
//         return {
//             static_cast<unsigned int>((width + BorderLeft + BorderRight) * TileSize),
//             static_cast<unsigned int>((height + BorderTop + BorderBottom) * TileSize)
//         };
//     }
//
//     [[nodiscard]] constexpr sf::Vector2f cellToPixel(int cellX, int cellY) noexcept {
//         return toPixels(cellX + BorderLeft, cellY + BorderTop);
//     }
//
//     [[nodiscard]] inline std::optional<sf::Vector2i> pixelToCell(sf::Vector2i pixel, int boardWidth, int boardHeight) noexcept {
//         const sf::IntRect bounds{
//             BorderLeft * TileSize,
//             BorderTop * TileSize,
//             boardWidth * TileSize,
//             boardHeight * TileSize
//         };
//         if (!bounds.contains(pixel)) return std::nullopt;
//
//         return sf::Vector2i{
//             (pixel.x - bounds.left) / TileSize,
//             (pixel.y - bounds.top) / TileSize
//         };
//     }
// }
//
// // Текстурные прямоугольники
// [[nodiscard]] constexpr sf::IntRect getTileRect(int tileIndex) noexcept {
//     return {tileIndex * TileSize, 0, TileSize, TileSize};
// }
//
// [[nodiscard]] constexpr sf::IntRect getMenuButtonRect(int posX, int posY) noexcept {
//     return {posX * TileSize * 5, posY * TileSize, TileSize * 5, TileSize};
// }

#endif // MINESWEEPER_LAYOUT_HPP
