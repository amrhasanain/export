#pragma once

#include "color.hpp"
#include <iostream>


void printUsage() {
    std::cout
        << color::yellow << "Usage:\n" << color::reset
        << "  export <name> <path-to-exe>\n"
        << "  export --help\n"
        << "  export --version\n\n"
        << color::gray
        << "Example:\n"
        << R"(  export duckpilot "C:\Tools\duckpilot.exe")"
        << color::reset << '\n';
}