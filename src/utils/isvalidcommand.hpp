#pragma once
#include <iostream>
#include <string>
#include <cctype>
bool isValidCommandName(const std::string& name) {
    if (name.empty()) {
        return false;
    }

    for (unsigned char ch : name) {
        if (!std::isalnum(ch) && ch != '_' && ch != '-') {
            return false;
        }
    }

    return true;
}