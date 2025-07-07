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

int main(int argc, char* argv[]) {
    filesync::context::DirectoryHandler dirH{"/repo/gbs/gbs-page/docs"};
    auto files = dirH.traverse();
    for (const auto& it : files) {
        std::cout << it << std::endl;
    }
    return 0;
}
