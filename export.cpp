#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

void createShim(
    const std::string& name,
    const fs::path& targetExe,
    const fs::path& exportProgram
) {
    const fs::path exportFolder = fs::absolute(exportProgram).parent_path();
    const fs::path shim = exportFolder / (name + ".cmd");

    std::ofstream out(shim);
    if (!out) {
        throw std::runtime_error("Could not create shim");
    }

    out << "@echo off\r\n"
        << "\"" << targetExe.string() << "\" %*\r\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: export <name> <path-to-exe>\n";
        return 1;
    }

    const std::string name = argv[1];
    const fs::path targetExe = argv[2];

    if (!fs::exists(targetExe) || !fs::is_regular_file(targetExe)) {
        std::cerr << "Executable not found: " << targetExe << '\n';
        return 1;
    }

    try {
        createShim(name, targetExe, argv[0]);
        std::cout << "Created shim: " << name << ".cmd\n";
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}