#pragma once

#include <memory>

#include "argparse.h"

namespace filesync::types {
struct File;
template <typename T> class SortedVector;
}

namespace filesync::context {

using FileVector = types::SortedVector<types::File>;

class Context {
    argparse::ArgumentParser parser;
    std::shared_ptr<FileVector> sourceFiles;
    std::shared_ptr<FileVector> targetFiles;

    void user_message(const std::string& msg) const;
    void user_message(const char* msg) const;

public:
    Context() {};
    ~Context() = default;
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(Context&&) = delete;

    int run(int argc, char* argv[]);
};

}
