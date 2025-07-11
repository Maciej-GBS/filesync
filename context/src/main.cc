#include <iostream>
#include <string>

#include "../inc/directory_handler.h"
#include <types/inc/sorted_vector.h>
#include <types/inc/file.h>
#include <sys/inc/log.h>

DECL_FORMAT(filesync::types::File, f) {
    os << "<file " << f.path << " hash=" << f.md5hash << ">";
    return os;
}

void analyze_dir(const char* path) {
    filesync::context::DirectoryHandler dirH{path};
    auto files = dirH.traverse();
    for (const auto& it : files) {
        std::cout << it << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::cout << filesync::format("Say goodbye %d", 991).c_str() << std::endl;
    return 0;
}
