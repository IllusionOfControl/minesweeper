#include <filesystem>
#include <iostream>

#include "Logger.hpp"
#include "MineSweeper.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

namespace {
    // Directory that holds the running executable, so resources copied next to
    // it can be found no matter what the current working directory is (C2).
    std::filesystem::path executableDir() {
#ifdef _WIN32
        wchar_t buffer[MAX_PATH];
        DWORD length = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
        if (length > 0 && length < MAX_PATH)
            return std::filesystem::path(std::wstring(buffer, length)).parent_path();
#endif
        return std::filesystem::current_path();
    }
}

int main() {
    Log::init();
    spdlog::info("Starting Minesweeper...");

    try {
        std::error_code ec;
        const auto workingDir = executableDir();
        std::filesystem::current_path(workingDir, ec);
        if (ec) {
            spdlog::warn("Failed to set working directory to {}: {}", workingDir.string(), ec.message());
        } else {
            spdlog::debug("Working directory set to: {}", workingDir.string());
        }

        MineSweeper app;
        app.run();

        spdlog::info("Minesweeper closed normally.");
    } catch (const std::exception &e) {
        spdlog::critical("Fatal unhandled exception: {}", e.what());
        return 1;
    }
    return 0;
}
