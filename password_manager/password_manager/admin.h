
#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User {
public:
    Admin(const std::string& username);
    void viewAllUsersPasswords();
    void manageUserPassword(const std::string& targetUser, const std::string& service, const std::string& newPassword);
    void deleteUserPassword(const std::string& targetUser, const std::string& service);
};

#endif 
