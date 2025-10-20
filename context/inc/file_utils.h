#pragma once

#include <string>

namespace filesync {

namespace types {
struct File;
template <typename T> class SortedVector;
}

namespace context {

types::SortedVector<types::File> traverse_directory(const std::string&);
types::SortedVector<types::File> traverse_directory(const std::string&, int maxDepth);

}
}
