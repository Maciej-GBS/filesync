#pragma once

#include <bitset>

namespace filesync::types {

using Hash16 = std::bitset<128>;
using Hash32 = std::bitset<256>;
using Hash64 = std::bitset<512>;

}
