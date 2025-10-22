#pragma once

#include <string>

namespace filesync {

namespace types {
struct File;
template <typename T> class SortedVector;
}

namespace context::file_utils {

types::SortedVector<types::File> traverse_directory(const std::string&);
types::SortedVector<types::File> traverse_directory(const std::string&, int maxDepth);
bool create_directory(const std::string& path);
bool copy_file(const std::string& source, const std::string& destination);

}
}
