#include <openssl/md5.h>

#include "../inc/hash_helper.h"

namespace filesync::hash {

types::Hash16 md5hash(const Data& input) {
    types::Hash16 hash;
    unsigned char* output = new unsigned char[MD5_DIGEST_LENGTH];
    
    MD5_CTX ctx;

    MD5(input.data(), input.size(), output);
    MD5_Init(&ctx);
    MD5_Update(&ctx, input.data(), input.size());
    MD5_Final(output, &ctx);
    hash = *(reinterpret_cast<types::Hash16*>(output));
    delete[] output;

    return hash;
}

}
