#include <iostream>
#include <string>
#include "hash/inc/hashing_model.h"

int main() {
    hash::Md5Hasher hasher;
    hash::Hash16 h1;

    std::vector<unsigned char> testData = {1, 3, 45, 21, 2, 3};
    h1 = hasher.hash(testData);

    std::cout << h1 << std::endl;

    return 0;
}
