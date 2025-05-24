#pragma once

#include <string>

namespace filesync {

namespace types {
struct File;
template <typename T> class SortedVector;
}

namespace context {

class DirectoryHandler {
    std::string dirPath;

public:
    DirectoryHandler(std::string path)
        : dirPath{path} {}
    ~DirectoryHandler() = default;

    types::SortedVector<types::File> traverse();
};

}
}
