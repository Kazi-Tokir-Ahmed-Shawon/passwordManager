
#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <ctime>
#include "encryptor.h"

class Password {
public:
    std::string username, service, encryptedPassword;
    time_t createDate, updateDate;

    Password();
    Password(const std::string& username, const std::string& service, const std::string& password);

    void updatePassword(const std::string& newPassword);
    std::string getDecryptedPassword() const;
};

#endif 
