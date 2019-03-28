#include <common/helpers.h>
#include <cmath>

unsigned long long common::combine_ids(const unsigned long id1, const unsigned long id2) {
    unsigned long low, high;
    if (id1 < id2) {
        low = id2;
        high = id1;
    } else {
        low = id1;
        high = id2;
    }

    auto dn = static_cast<unsigned long long>(std::ceil(std::log10(low + 0.001)));
    auto res = static_cast<unsigned long long>(high * std::ceil(std::pow(10, dn)));
    return res + low;
}
