#include <openssl/md5.h>

#include "../inc/hash_helper.h"

namespace filesync::hash {

types::Hash16 md5hash(const Data& input) {
    types::Hash16 hash;
    unsigned char* output = new unsigned char[MD5_DIGEST_LENGTH];
    
    MD5_CTX ctx;

    MD5_Init(&ctx);
    MD5_Update(&ctx, input.data(), input.size());
    MD5_Final(output, &ctx);
    for (size_t i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        hash <<= 8;
        hash |= types::Hash16{static_cast<unsigned long long>(output[i])};
    }
    delete[] output;

    return hash;
}

}

/* https://docs.openssl.org/3.4/man7/ossl-guide-libcrypto-introduction/
#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>

int main(void)
{
    EVP_MD_CTX *ctx = NULL;
    EVP_MD *sha256 = NULL;
    const unsigned char msg[] = {
        0x00, 0x01, 0x02, 0x03
    };
    unsigned int len = 0;
    unsigned char *outdigest = NULL;
    int ret = 1;

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL)
        goto err;

    // should be done once
    sha256 = EVP_MD_fetch(NULL, "SHA256", NULL);
    if (sha256 == NULL)
            goto err;

   if (!EVP_DigestInit_ex(ctx, sha256, NULL))
       goto err;

    if (!EVP_DigestUpdate(ctx, msg, sizeof(msg)))
        goto err;

    outdigest = OPENSSL_malloc(EVP_MD_get_size(sha256));
    if (outdigest == NULL)
        goto err;

    if (!EVP_DigestFinal_ex(ctx, outdigest, &len))
        goto err;

    BIO_dump_fp(stdout, outdigest, len);

    ret = 0;

 err:
    OPENSSL_free(outdigest);
    EVP_MD_free(sha256);
    EVP_MD_CTX_free(ctx);
    if (ret != 0)
       ERR_print_errors_fp(stderr);
    return ret;
}
*/
