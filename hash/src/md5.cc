#include "../inc/hashing_model.h"
#include <openssl/md5.h>

namespace hash {

class Md5Hasher : public IHashingModel<Hash16> {
};

}
