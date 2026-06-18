#include <filesystem>
#include <iostream>
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
    try {
        std::error_code ec;
        std::filesystem::current_path(executableDir(), ec);

        MineSweeper();
    } catch (const std::exception &e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
