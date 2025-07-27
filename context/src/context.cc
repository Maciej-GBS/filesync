#include <algorithm>
#include <iostream>

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

template <class InputIt, typename Predicate>
InputIt takeWhile(InputIt it, const InputIt& end, Predicate pred) {
    while (it != end) {
        if (!pred(*it)) {
            return it;
        }
        ++it;
    }
    return end;
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

    user_message(format("Using source directory: %s", FORMATSTR(srcDir)));
    sourceFiles = std::make_shared<FileVector>(read_directory(srcDir));
    if (srcDir.compare(targetDir) != 0) {
        user_message(format("Using destination directory: %s", FORMATSTR(targetDir)));
        targetFiles = std::make_shared<FileVector>(read_directory(targetDir));
    }
    else {
        user_message("Using same directory as source and destination!");
        targetFiles = sourceFiles;
    }

    for (const auto& file : *sourceFiles) {
        const auto targetIt = std::lower_bound(targetFiles->begin(), targetFiles->end(), file);
        if (targetIt != targetFiles->end()) {
            user_message(format(
                "File %s already exists at target %s [%s]", FORMATSTR(file.path), FORMATSTR(targetIt->path), FORMATSTR(file.hash)));
            if (!parser.is_find_duplicates()) {
                continue;
            }
            const auto endDuplicates = takeWhile(
                targetIt, targetFiles->end(), [&file](const types::File& f) { return file == f; });
            if (targetIt == endDuplicates) {
                continue;
            }
            std::for_each(targetIt + 1, endDuplicates, [&file, this](const types::File& f) {
                std::cout << file << " = " << f << std::endl;
            });
        }
        else {
            // TODO copy from source to destination
        }
    }

    return 0;
}

}
