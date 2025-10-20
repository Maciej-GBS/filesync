#pragma once

#include <bitset>

#include <sys/inc/streamable.h>

namespace filesync::types {

namespace {
template <size_t N>
std::ostream& format_bitset(std::ostream& os, const std::bitset<N>& hash) {
    std::string binary = hash.to_string();
    os << std::hex;
    for (size_t i = 0; i < binary.length(); i += 4) {
        std::bitset<4> nibble{binary.substr(i, 4)};
        os << nibble.to_ulong();
    }
    return os;
}
}

using Hash16 = std::bitset<128>;
using Hash32 = std::bitset<256>;
using Hash64 = std::bitset<512>;

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
