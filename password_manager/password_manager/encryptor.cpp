
#include "encryptor.h"

std::string Encryptor::encrypt(const std::string& password) {
    std::string encrypted = password;
    for (char& c : encrypted) c += 3;
    return encrypted;
}

std::string Encryptor::decrypt(const std::string& password) {
    std::string decrypted = password;
    for (char& c : decrypted) c -= 3;
    return decrypted;
}
