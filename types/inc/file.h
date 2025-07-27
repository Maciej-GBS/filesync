#pragma once

#include <string>

#include "hash.h"

namespace filesync::types {

struct File {
    std::string path;
    Hash16 md5hash;
    // basename TODO

    File(std::string p, Hash16 h) : path{p}, md5hash{h} {}

    bool operator<(const File& o) const { return md5hash < o.md5hash; }
    bool operator==(const File& o) const { return md5hash == o.md5hash; }
};

}
