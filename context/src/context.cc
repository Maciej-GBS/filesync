#include <iostream>
#include <memory>

#include "../inc/context.h"
#include "../inc/directory_handler.h"
#include <types/inc/file.h>
#include <types/inc/sorted_vector.h>
#include <sys/inc/log.h>

namespace filesync::context {

namespace {
FileVector read_directory(const std::string& dir) {
    DirectoryHandler handler{dir};
    return handler.traverse();
}
}

void Context::user_message(const std::string& msg) const {
    user_message(msg.c_str());
}

void Context::user_message(const char* msg) const {
    if (parser.is_verbose()) {
        std::cout << msg << std::endl;
    }
}

int Context::run(int argc, char* argv[]) {
    parser.parse_args(argc, argv);

    const std::string& srcDir{parser.get_source_directory()};
    const std::string& targetDir{parser.get_destination_directory()};

    user_message(format("Using source directory: %s", srcDir));
    sourceFiles = std::make_shared<FileVector>(read_directory(srcDir));
    if (srcDir.compare(targetDir) != 0) {
        user_message(format("Using destination directory: %s", targetDir));
        targetFiles = std::make_shared<FileVector>(read_directory(targetDir));
    }
    else {
        user_message("Using same directory as source and destination!");
        targetFiles = sourceFiles;
    }

    return 0;
}

}
