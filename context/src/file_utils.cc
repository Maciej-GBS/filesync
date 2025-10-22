#include <cstring>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "../inc/file_utils.h"
#include <hash/inc/hash_helper.h>
#include <types/inc/file.h>
#include <types/inc/sorted_vector.h>

namespace filesync::context::file_utils {

namespace {
constexpr int MAX_DEPTH = 20;
constexpr size_t MAX_FILE_SIZE = 1024 * 1024 * 1024; // 1GB limit

types::File create_file_element(const std::string& filePath) {
    std::ifstream binaryFile{filePath, std::ios::binary};

    if (!binaryFile) {
        throw std::runtime_error{"Failed to open file: " + filePath};
    }

    std::istreambuf_iterator<char> start(binaryFile);
    std::istreambuf_iterator<char> end;

    hash::Data fileData;
    size_t bytesRead = 0;

    for (auto it = start; it != end && bytesRead < MAX_FILE_SIZE; ++it, ++bytesRead) {
        fileData.push_back(*it);
    }

    return types::File{filePath, hash::md5hash(fileData), fileData.size()};
}
}

types::SortedVector<types::File> traverse_directory(const std::string& dirPath) {
    return traverse_directory(dirPath, MAX_DEPTH);
}

types::SortedVector<types::File> traverse_directory(const std::string& dirPath, int depth) {
    types::SortedVector<types::File> files;

    if (depth < 0) {
        return files;
    }

    for (const auto& f : std::filesystem::directory_iterator(dirPath)) {
        if (f.is_directory()) {
            const auto scopedFiles{traverse_directory(f.path(), depth - 1)};
            files.insert(scopedFiles.begin(), scopedFiles.end());
        }
        else if (f.is_regular_file() || f.is_block_file() || f.is_character_file()) {
            files.insert(create_file_element(f.path()));
        }
    }

    return files;
}

bool create_directory(const std::string& path) {
    std::error_code ec;
    return std::filesystem::create_directories(path, ec);
}

bool copy_file(const std::string& source, const std::string& destination) {
    std::error_code ec;
    const auto destinationDir{destination.substr(0, destination.find_last_of('/'))};

    if (!std::filesystem::exists(destinationDir)) {
        create_directory(destinationDir);
    }
    return std::filesystem::copy_file(source, destination, ec);
}

}
