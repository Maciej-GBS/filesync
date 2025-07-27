#include <cstring>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "../inc/directory_handler.h"
#include <hash/inc/hash_helper.h>
#include <types/inc/file.h>
#include <types/inc/sorted_vector.h>
#include <sys/inc/log.h>

namespace filesync::context {

namespace {
constexpr int BUF_SIZE = 256;

types::File create_file_element(const std::string& filePath) {
    std::ifstream binaryFile{filePath, std::ios::binary};
    hash::Data fileData;
    char* buffer = new char[BUF_SIZE];

    if (!binaryFile) {
        throw std::runtime_error{format("Failed to open file: %s", filePath.c_str())};
    }

    std::streamsize bufUsed = 1;
    while (bufUsed > 0 && binaryFile.good() && !binaryFile.eof()) {
        bufUsed = binaryFile.readsome(buffer, BUF_SIZE);
        fileData.insert(fileData.end(), buffer, buffer + bufUsed * sizeof(char));
    }
    binaryFile.close();
    delete[] buffer;

    return types::File{filePath, hash::md5hash(fileData), fileData.size()};
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
            files.insert(create_file_element(f.path()));
        }
    }

    return files;
}

}
