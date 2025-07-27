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
        if (!pred(*it++)) {
            return it;
        }
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

    std::vector<types::Hash16> targetHashes;
    targetHashes.reserve(targetFiles->size());
    std::transform(
        targetFiles->begin(),
        targetFiles->end(),
        std::back_inserter(targetHashes),
        [](const auto& f) { return f.md5hash; }
    );
    bool result;
    for (const auto& file : *sourceFiles) {
        auto hashEqPred = [&file](const types::File& f) {
            return file.md5hash == f.md5hash;
        };
        result = std::binary_search(targetHashes.begin(), targetHashes.end(), file.md5hash);
        if (result) {
            user_message(format("File %s already exists at target hash = %i", file.path, file.md5hash));
            if (!parser.is_find_duplicates()) {
                continue;
            }
            // TODO optimize with binary search? switch to map?
            const auto& firstOccurence = std::find_if(targetFiles->begin(), targetFiles->end(), hashEqPred);
            if (firstOccurence == targetFiles->end()) {
                throw std::runtime_error("Target file reference could not be found!");
            }
            const auto endDuplicates = takeWhile(firstOccurence, targetFiles->end(), hashEqPred);
            std::for_each(firstOccurence, endDuplicates, [&file](const types::File& f) {
                std::cout << file.path << " = " << f.path << std::endl;
            });
        }
        else {
            // TODO copy from source to destination
        }
    }

    return 0;
}

}
