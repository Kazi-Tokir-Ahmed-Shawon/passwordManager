
#ifndef USER_H
#define USER_H

#include <string>
#include "file_handler.h"

class User {
public:
    std::string username;

    User(const std::string& username);
    void storePassword(const std::string& service, const std::string& password);
    void viewPasswords();
    void updatePassword(const std::string& service);
    void deletePassword(const std::string& service);
};

#endif 
