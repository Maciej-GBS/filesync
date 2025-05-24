#pragma once

#include "hash.h"

namespace filesync::types {

struct File {
    char* path;
    Hash16 md5hash;
} File;

}
