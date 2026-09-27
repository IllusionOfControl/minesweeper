#ifndef MINESWEEPER_DIFFICULTY_HPP
#define MINESWEEPER_DIFFICULTY_HPP

#include <algorithm>
#include <optional>


class Difficulty {
public:
    enum class Preset {
        Easy,
        Medium,
        Hard,
        Custom
    };

    struct Limits {
        static constexpr int MinWidth = 5;
        static constexpr int MaxWidth = 32;
        static constexpr int MinHeight = 5;
        static constexpr int MaxHeight = 24;
        static constexpr int MinMines = 1;

        static constexpr int maxMinesFor(const int width, const int height) noexcept {
            return std::max(MinMines, (width * height) - 1);
        }
    };

    [[nodiscard]] static constexpr Difficulty create(const Preset preset) noexcept {
        switch (preset) {
        case Preset::Easy: return {9, 9, 10, Preset::Easy};
        case Preset::Medium: return {16, 16, 40, Preset::Medium};
        case Preset::Hard: return {32, 16, 99, Preset::Hard};
        case Preset::Custom: return {9, 9, 10, Preset::Custom};
        }
        return {9, 9, 10, Preset::Easy};
    }

    [[nodiscard]] static constexpr std::optional<Difficulty> createCustom(const int width, const int height, const int mines) noexcept {
        if (!isValid(width, height, mines)) { return std::nullopt; }
        return Difficulty(width, height, mines, Preset::Custom);
    }

    [[nodiscard]] static constexpr bool isValid(const int width, const int height, const int mines) noexcept {
        if (width < Limits::MinWidth || width > Limits::MaxWidth) return false;
        if (height < Limits::MinHeight || height > Limits::MaxHeight) return false;
        if (mines < Limits::MinMines || mines > Limits::maxMinesFor(width, height)) return false;
        return true;
    }

    [[nodiscard]] constexpr int getWidth() const noexcept { return mWidth; }
    [[nodiscard]] constexpr int getHeight() const noexcept { return mHeight; }
    [[nodiscard]] constexpr int getMineCount() const noexcept { return mMineCount; }
    [[nodiscard]] constexpr int getTotalCells() const noexcept { return mWidth * mHeight; }
    [[nodiscard]] constexpr Preset getPreset() const noexcept { return mPreset; }

    [[nodiscard]] constexpr bool operator==(const Difficulty& other) const noexcept {
        return mWidth == other.mWidth &&
               mHeight == other.mHeight &&
               mMineCount == other.mMineCount;
    }

private:
    constexpr Difficulty(const int width, const int height, const int mines, const Preset preset) noexcept
        : mWidth(width)
          , mHeight(height)
          , mMineCount(mines)
          , mPreset(preset) {}

    int mWidth;
    int mHeight;
    int mMineCount;
    Preset mPreset;
};

inline const char* toString(const Difficulty::Preset preset) noexcept {
    switch (preset) {
    case Difficulty::Preset::Easy: return "Easy";
    case Difficulty::Preset::Medium: return "Medium";
    case Difficulty::Preset::Hard: return "Hard";
    case Difficulty::Preset::Custom: return "Custom";
    }
    return "Unknown";
}

#endif //MINESWEEPER_DIFFICULTY_HPP
