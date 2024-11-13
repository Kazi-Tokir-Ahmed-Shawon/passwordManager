
#include "password.h"

Password::Password() : username(""), service(""), encryptedPassword(""), createDate(0), updateDate(0) {}

Password::Password(const std::string& username, const std::string& service, const std::string& password)
    : username(username), service(service), encryptedPassword(Encryptor::encrypt(password)) {
    createDate = updateDate = time(nullptr);
}

void Password::updatePassword(const std::string& newPassword) {
    encryptedPassword = Encryptor::encrypt(newPassword);
    updateDate = time(nullptr);
}

std::string Password::getDecryptedPassword() const {
    return Encryptor::decrypt(encryptedPassword);
}
