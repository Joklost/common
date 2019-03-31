#ifndef COMMON_STRING_H
#define COMMON_STRING_H

#include <deque>
#include <string>

namespace common {
    std::deque<std::string> split(const std::string &string, const std::string &delim);
}

#endif /* COMMON_STRING_H */
