#include "hash_utils.h"
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>

std::string hash_utils::sha256(const std::string& str) {
    // ... implementation of sha256 ...


    unsigned char hash[EVP_MAX_MD_SIZE]; // Buffer for the hash
    unsigned int lengthOfHash = 0;

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        throw std::runtime_error("Failed to create hash context");
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to initialize hash context");
    }

    if (EVP_DigestUpdate(context, str.c_str(), str.size()) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to update hash");
    }

    if (EVP_DigestFinal_ex(context, hash, &lengthOfHash) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to finalize hash");
    }

    std::stringstream ss;
    for (unsigned int i = 0; i < lengthOfHash; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    EVP_MD_CTX_free(context);
    return ss.str();
}
