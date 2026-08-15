#ifndef MINESWEEPER_RESOURCEIDENTIFIERS_HPP
#define MINESWEEPER_RESOURCEIDENTIFIERS_HPP

enum class TextureID {
    Tiles,
    Logo,
    Background,
    Smiles,
    Second,
    CustomDifficultyButtons,
    DifficultyMenuButtons,
    StateButtons,
    MainMenuButtons,
    LedBackground
};

enum class FontID {
    Default
};

inline const char* toString(const TextureID id) noexcept {
    switch (id) {
    case TextureID::Tiles: return "Tiles";
    case TextureID::Logo: return "Logo";
    case TextureID::Background: return "Background";
    case TextureID::Smiles: return "Smiles";
    case TextureID::Second: return "Second";
    case TextureID::CustomDifficultyButtons: return "CustomDifficultyButtons";
    case TextureID::DifficultyMenuButtons: return "DifficultyMenuButtons";
    case TextureID::StateButtons: return "StateButtons";
    case TextureID::MainMenuButtons: return "MainMenuButtons";
    case TextureID::LedBackground: return "LedBackground";
    }
    return "UnknownTexture";
}

inline const char* toString(const FontID id) noexcept {
    switch (id) {
    case FontID::Default: return "DefaultFont";
    }
    return "UnknownFont";
}

#endif // MINESWEEPER_RESOURCEIDENTIFIERS_HPP