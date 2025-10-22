#pragma once

#include <bitset>
#include <sstream>

#include <sys/inc/streamable.h>

namespace filesync::types {

namespace {
template <size_t N>
std::ostream& format_bitset(std::ostream& os, const std::bitset<N>& hash) {
    std::ostringstream ossHex;
    std::string binary = hash.to_string();
    ossHex << std::hex;
    for (size_t i = 0; i < binary.length(); i += 4) {
        std::bitset<4> nibble{binary.substr(i, 4)};
        ossHex << nibble.to_ulong();
    }
    os << ossHex.str();
    return os;
}
}

using Hash16 = std::bitset<128>;
using Hash32 = std::bitset<256>;
using Hash64 = std::bitset<512>;

template <size_t N>
bool operator<(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
    for (size_t i = 0; i < N; ++i) {
        if (lhs[i] != rhs[i]) {
            return lhs[i] < rhs[i];
        }
    }
    return false;
}

DECL_FORMAT(Hash16, hash) {
    return format_bitset(os, hash);
}

DECL_FORMAT(Hash32, hash) {
    return format_bitset(os, hash);
}

DECL_FORMAT(Hash64, hash) {
    return format_bitset(os, hash);
}

}
