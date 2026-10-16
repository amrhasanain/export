#pragma once
#include "color.hpp"
#include <iostream>

void printBanner() {
    std::cout
        << color::cyan
        << R"(
  _____                       _
 | ____|_  ___ __   ___  _ __| |_
 |  _| \ \/ / '_ \ / _ \| '__| __|
 | |___ >  <| |_) | (_) | |  | |_
 |_____/_/\_\ .__/ \___/|_|   \__|
            |_|
)"
        << color::reset
        << color::gray
        << "  Windows command alias manager\n\n"
        << color::reset;
}