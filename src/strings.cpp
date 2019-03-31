#include <common/strings.h>

std::deque<std::string> common::split(const std::string &string, const std::string &delim) {
    std::deque<std::string> tokens{};
    size_t prev{}, pos{};

    do {
        pos = string.find(delim, prev);
        if (pos == std::string::npos) {
            pos = string.length();
        }

        std::string token = string.substr(prev, pos - prev);
        if (!token.empty()) {
            tokens.push_back(token);
        }
        prev = pos + delim.length();
    } while (pos < string.length() && prev < string.length());
    return tokens;
}