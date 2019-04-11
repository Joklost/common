#ifndef COMMON_STRING_H
#define COMMON_STRING_H

#include <string>

#include "queue.h"

namespace common {
    common::DoubleEndedQueue<std::string> split(const std::string &string, const std::string &delim);
}

#endif /* COMMON_STRING_H */
