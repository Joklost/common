#ifndef COMMON_EQUALITY_H
#define COMMON_EQUALITY_H

#include <cmath>
#include <limits>

namespace common {
    template<typename T>
    bool is_equal(T left, T right) {
        return std::fabs(left - right) < std::numeric_limits<T>::epsilon();
    }

    template<typename T>
    bool is_equal(T left, T right, T epsilon) {
        return std::fabs(left - right) < epsilon;
    }
    
    template<typename T>
    struct is_less {
        bool operator()(const T &left, const T &right) const {
            return (!is_equal(left, right) && (left < right));
        }
    };

    template<typename T>
    bool is_zero(T left) {
        return is_equal(left, (T) 0.0);
    }

}

#endif /* COMMON_EQUALITY_H */
