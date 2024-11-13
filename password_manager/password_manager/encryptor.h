
#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <string>

class Encryptor {
public:
    static std::string encrypt(const std::string& password);
    static std::string decrypt(const std::string& password);
};

#endif 
