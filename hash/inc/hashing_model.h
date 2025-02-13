#pragma once

#include <vector>

namespace hash {

using Data = std::vector<unsigned char>;
using Hash16 = unsigned short int;
using Hash32 = unsigned int;
using Hash64 = unsigned long long int;

template <typename T> class IHashingModel {
public:
    virtual T hash(const Data& input) const = 0;
};

class Md5Hasher : public IHashingModel<Hash16> {
public:
    Md5Hasher() = default;
    ~Md5Hasher() = default;

    Hash16 hash(const Data& input) const override;
};

}
