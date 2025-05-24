#include <cstring>
#include <fstream>
#include <filesystem>

#include "../inc/directory_handler.h"
#include <hash/inc/hash_helper.h>
#include <types/inc/file.h>
#include <types/inc/sorted_vector.h>
#include <sys/inc/log.h>

namespace filesync::context {

namespace {
types::File checksumFile(const std::string& filePath) {
    std::ifstream binaryFile{filePath, std::ios::binary};
    if (!binaryFile) {
        throw std::runtime_error{format("Failed to open file: ", filePath.c_str())};
    }
    return types::File{filePath, hash::md5hash(hash::Data{0})};
}
}


types::SortedVector<types::File> DirectoryHandler::traverse() {
    types::SortedVector<types::File> files;
    
    for (const auto& f : std::filesystem::directory_iterator(dirPath)) {
        if (f.is_directory()) {
            DirectoryHandler scopedHandler{f.path()};
            const auto& scopedFiles{scopedHandler.traverse()};
            files.insert(scopedFiles.begin(), scopedFiles.end());
        }
        else if (f.is_regular_file() || f.is_block_file() || f.is_character_file()) {
            files.insert(checksumFile(f.path()));
        }
    }

    return files;
}

}
