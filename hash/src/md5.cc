#include "../inc/hashing_model.h"
#include <openssl/md5.h>

namespace hash {

Hash16 Md5Hasher::hash(const Data& input) const {
    Hash16 hash;
    unsigned char* output = new unsigned char[MD5_DIGEST_LENGTH];
    
    MD5_CTX ctx;

    MD5(input.data(), input.size(), output);
    MD5_Init(&ctx);
    MD5_Update(&ctx, input.data(), input.size());
    MD5_Final(output, &ctx);
    hash = *(reinterpret_cast<Hash16*>(output));
    delete[] output;

    return hash;
}

}
