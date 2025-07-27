#pragma once

#include <string>

#include "hash.h"

namespace filesync::types {

namespace {
template <size_t S>
bool operator<(std::bitset<S> lhs, std::bitset<S> rhs) {
    auto n_bits{lhs.size()};
    for (size_t i = 0; i < n_bits; ++i) {
        if (lhs.test(i)) {
            return false;
        }
        else if (rhs.test(i)) {
            return true;
        }
    }
    return false;
}
}

struct File {
    std::string path;
    Hash16 hash;

    File(std::string p, Hash16 h) : path{p}, hash{h} {}

    bool operator<(const File& o) const { return hash < o.hash; }
    bool operator==(const File& o) const { return hash == o.hash; }

    const char* basename() const {
        auto cut = path.find_last_of('/');
        if (cut == std::string::npos) {
            return path.c_str();
        }
        return &(path.c_str()[cut]);
    }
};

}
