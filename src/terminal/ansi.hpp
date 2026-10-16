#pragma once
#ifdef _WIN32
#include <windows.h>
#endif
void enableAnsiColors() {
#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (console == INVALID_HANDLE_VALUE) {
        return;
    }

    DWORD mode = 0;
    if (GetConsoleMode(console, &mode)) {
        SetConsoleMode(console, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

    HANDLE errorConsole = GetStdHandle(STD_ERROR_HANDLE);
    if (errorConsole != INVALID_HANDLE_VALUE &&
        GetConsoleMode(errorConsole, &mode)) {
        SetConsoleMode(
            errorConsole,
            mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING
        );
    }
#endif
}