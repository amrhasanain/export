#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <stdexcept>
namespace fs = std::filesystem;



void createShim(
    const std::string& name,
    const fs::path& targetExe,
    const fs::path& exportProgram
) {
    const fs::path exportFolder =
        fs::absolute(exportProgram).parent_path();

    const fs::path shim = exportFolder / (name + ".cmd");

    std::ofstream out(shim);
    if (!out) {
        throw std::runtime_error("Could not create shim file");
    }

    out << "@echo off\r\n"
        << "\"" << targetExe.string() << "\" %*\r\n";

    if (!out) {
        throw std::runtime_error("Could not write shim file");
    }
}