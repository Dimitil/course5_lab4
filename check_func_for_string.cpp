#include "check_func_for_string.h"


bool alphaCheck(const std::string& str) {
    for (const auto& ch : str) {
        if (!isalpha(ch)) return false;
    }
    return true;
}

bool digitCheck(const std::string& str) {
    for (const auto& ch : str) {
        if (!isdigit(ch)) return false;
    }
    return true;
}

bool noAlphaNoDig(const std::string& str) {
    for (const auto& ch : str) {
        if (isdigit(ch) || isalpha(ch)) return false;
    }
    return true;
}
