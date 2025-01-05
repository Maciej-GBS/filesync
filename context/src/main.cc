#include <iostream>
#include <string>
#include "../../hash/inc/hashing_model.h"

int main() {
    hash::Hash16 h1;
    hash::Hash32 h2;
    hash::Hash64 h3;
    std::cout << sizeof(h1) << ":" << sizeof(hash::Hash16) << std::endl;
    std::cout << sizeof(h2) << ":" << sizeof(hash::Hash32) << std::endl;
    std::cout << sizeof(h3) << ":" << sizeof(hash::Hash64) << std::endl;

    return 0;
}
