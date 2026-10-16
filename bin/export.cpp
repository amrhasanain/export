#include <exception>
#include <filesystem>
#include <iostream>
#include <string>

#include "../src/terminal/ansi.hpp"
#include "../src/terminal/banner.hpp"
#include "../src/terminal/color.hpp"
#include "../src/terminal/usage.hpp"
#include "../src/utils/createshim.hpp"
#include "../src/utils/isvalidcommand.hpp"

int main(int argc, char* argv[]) {
    enableAnsiColors();
    printBanner();

    if (argc == 2) {
        const std::string option = argv[1];

        if (option == "--version" || option == "-version" ||
            option == "-v") {
            std::cout << "export 1.0.0\n";
            return 0;
        }

        if (option == "--help" || option == "-h") {
            printUsage();
            return 0;
        }
    }

    if (argc != 3) {
        std::cerr << color::red
                << "Error: Invalid arguments.\n\n"
                << color::reset;
        printUsage();
        return 1;
    }

    const std::string name = argv[1];
    const fs::path targetExe = argv[2];

    if (!isValidCommandName(name)) {
        std::cerr << color::red
                << "Error: Command name can contain only letters, "
                "numbers, '_' and '-'.\n"
                << color::reset;
        return 1;
    }

    try {
        if (!fs::exists(targetExe) || !fs::is_regular_file(targetExe)) {
            std::cerr << color::red
                    << "Error: Executable file was not found:\n  "
                    << targetExe.string() << '\n'
                    << color::reset;
            return 1;
        }

        createShim(name, targetExe, argv[0]);

        std::cout << color::green
                << "Success! Created command: "
                << name << ".cmd\n"
                << color::reset
                << color::gray
                << "The export program's folder must be in PATH "
                "to use this command from other locations.\n"
                << color::reset;
    } catch (const std::exception& error) {
        std::cerr << color::red
                << "Error: " << error.what() << '\n'
                << color::reset;
        return 1;
    }
    return 0;
}