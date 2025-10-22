#include <algorithm>
#include <iostream>

#include "../inc/context.h"
#include "../inc/file_utils.h"
#include <types/inc/file.h>
#include <types/inc/sorted_vector.h>
#include <sys/inc/log.h>

namespace filesync::context {

namespace {
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

int Context::run(int argc, char* argv[]) {
    parser.parse_args(argc, argv);

    const bool isVerbose{parser.is_verbose()};
    const std::string& srcDir{parser.get_source_directory()};
    const std::string& targetDir{parser.get_destination_directory()};

    LOG("Using source directory: %s", FORMATSTR(srcDir));
    sourceFiles = std::make_shared<FileVector>(file_utils::traverse_directory(srcDir));
    if (srcDir.compare(targetDir) != 0) {
        LOG("Using destination directory: %s", FORMATSTR(targetDir));
        targetFiles = std::make_shared<FileVector>(file_utils::traverse_directory(targetDir));
    }
    else {
        LOG("Using same directory as source and destination!");
        targetFiles = sourceFiles;
    }

    for (const auto& file : *sourceFiles) {
        const auto targetIt = std::lower_bound(targetFiles->begin(), targetFiles->end(), file);
        if (targetIt != targetFiles->end() && *targetIt == file) {
            if (isVerbose) {
                LOG("File %s already exists at target %s", FORMATSTR(file), FORMATSTR(*targetIt));
            }
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
            const auto sourceRelativePath{file.path.substr(srcDir.size())};
            const auto targetPath{targetDir + sourceRelativePath};

            if (parser.is_dry_run()) {
                LOG("Would copy file %s to %s", FORMATSTR(file.path), FORMATSTR(targetPath));
                continue;
            }

            if (isVerbose) [[likely]] {
                LOG("Copying file %s to %s", FORMATSTR(file.path), FORMATSTR(targetPath));
            }
            if (!file_utils::copy_file(file.path, targetPath)) {
                LOG("Failed to copy file %s", FORMATSTR(file.path));
                continue;
            }
        }
    }

    return 0;
}

}
