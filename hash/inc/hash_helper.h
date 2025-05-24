#pragma once

#include <vector>

#include <types/inc/hash.h>

namespace filesync::hash {

using Data = std::vector<unsigned char>;

types::Hash16 md5hash(const Data& input);

}
