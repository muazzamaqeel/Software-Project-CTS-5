#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <string>

class hash_utils {
public:
    std::string sha256(const std::string& str);
};

#endif // HASH_UTILS_H
