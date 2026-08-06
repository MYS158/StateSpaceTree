#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

/// ANSI escape codes for terminal color and formatting.
namespace ansi {
    constexpr const char* reset  = "\033[0m";
    constexpr const char* bold   = "\033[1m";
    constexpr const char* red    = "\033[31m";
    constexpr const char* green  = "\033[32m";
    constexpr const char* yellow = "\033[33m";
    constexpr const char* cyan   = "\033[36m";
}

/// Enables ANSI escape code processing and UTF-8 output on Windows; no-op elsewhere.
inline void enable_ansi() {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(h, &mode))
        SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    (void)SetConsoleOutputCP(CP_UTF8);
#endif
}
