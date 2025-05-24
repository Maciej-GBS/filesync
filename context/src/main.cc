#include <iostream>
#include <string>

#include <hash/inc/hash_helper.h>
#include <sys/inc/log.h>

int main(int argc, char* argv[]) {
    filesync::types::Hash16 h1;

    std::vector<unsigned char> testData = {3, 3, 45, 21, 2, 3};
    h1 = filesync::hash::md5hash(testData);

    std::cout << filesync::format("Calculated hash = ", FORMATSTRING(h1)) << std::endl;

    return 0;
}
