#pragma once

#include <vector>

namespace hash {

using Data = std::vector<char>;
using Hash16 = unsigned short int;
using Hash32 = unsigned int;
using Hash64 = unsigned long long int;

template <typename T> class IHashingModel {
public:
    virtual T hash(const Data& input) const = 0;
};

}
