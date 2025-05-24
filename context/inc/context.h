#pragma once

#include "argparse.h"

namespace filesync::context {

class Context {

public:
    Context();
    ~Context() = default;
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(Context&&) = delete;
};

}
