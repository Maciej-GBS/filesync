#include "../inc/context.h"

#include "../inc/directory_handler.h"
#include <types/inc/file.h>
#include <types/inc/sorted_vector.h>

namespace filesync::context {

namespace {
types::SortedVector<types::File> read_directory(std::string& dir) {
    DirectoryHandler handler{dir};
    return handler.traverse();
}
}

int Context::run(int argc, char* argv[]) {
    parser.parse_args(argc, argv);
    return 0;
}

}
