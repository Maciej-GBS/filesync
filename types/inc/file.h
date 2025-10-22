#pragma once

#include <string>

#include "hash.h"
#include <sys/inc/streamable.h>

namespace filesync::types {

struct File {
    std::string path;
    Hash16 hash;
    size_t contentLength;

    File(std::string p, Hash16 h, size_t l) : path{p}, hash{h}, contentLength{l} {}

    bool operator<(const File& o) const { return hash < o.hash; }
    bool operator==(const File& o) const { return (hash ^ o.hash).none(); }

    const char* basename() const {
        auto cut = path.find_last_of('/');
        if (cut == std::string::npos) {
            return path.c_str();
        }
        return &(path.c_str()[cut]);
    }
};

DECL_FORMAT(File, file) {
    os << "{" << file.path << " (" << file.contentLength << ") [" << file.hash << "]}";
    return os;
}

}
