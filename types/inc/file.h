#pragma once

#include <string>

#include "hash.h"

namespace filesync::types {

struct File {
    std::string path;
    Hash16 md5hash;

    File(std::string p, Hash16 h) : path{p}, md5hash{h} {}
};

}
