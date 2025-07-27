#include <memory>

#include "../inc/context.h"
#include "../inc/directory_handler.h"
#include <types/inc/file.h>
#include <types/inc/sorted_vector.h>

namespace filesync::context {

namespace {
FileVector read_directory(const std::string& dir) {
    DirectoryHandler handler{dir};
    return handler.traverse();
}
}

int Context::run(int argc, char* argv[]) {
    parser.parse_args(argc, argv);

    sourceFiles = std::make_shared<FileVector>(read_directory(parser.get_source_directory()));
    if (parser.get_source_directory().compare(parser.get_destination_directory()) != 0) {
        targetFiles = std::make_shared<FileVector>(read_directory(parser.get_destination_directory()));
    }
    else {
        targetFiles = sourceFiles;
    }

    return 0;
}

}
