
#include "admin.h"
#include <iostream>

Admin::Admin(const std::string& username) : User(username) {}

void Admin::viewAllUsersPasswords() {
    auto passwords = FileHandler::loadPasswords();
    for (const auto& pair : passwords) {
        std::cout << "User: " << pair.first << std::endl;
        for (int i = 0; i < pair.second.getSize(); ++i) {
            const Password& password = pair.second[i];
            std::cout << "  Service: " << password.service
                << ", Password: " << password.getDecryptedPassword() << std::endl;
        }
    }
}

void Admin::manageUserPassword(const std::string& targetUser, const std::string& service, const std::string& newPassword) {
    auto passwords = FileHandler::loadPasswords();
    bool found = false;

    for (int i = 0; i < passwords[targetUser].getSize(); ++i) {
        Password& password = passwords[targetUser][i];
        if (password.service == service) {
            password.updatePassword(newPassword);
            found = true;
            break;
        }
    }
    if (found) {
        FileHandler::overwritePasswords(passwords);
        std::cout << "Password for user " << targetUser << " updated successfully.\n";
    }
    else {
        std::cout << "Service not found for user " << targetUser << ".\n";
    }
}

void Admin::deleteUserPassword(const std::string& targetUser, const std::string& service) {
    auto passwords = FileHandler::loadPasswords();
    bool found = false;

    for (int i = 0; i < passwords[targetUser].getSize(); ++i) {
        if (passwords[targetUser][i].service == service) {
            passwords[targetUser].remove(i);
            found = true;
            FileHandler::overwritePasswords(passwords);
            std::cout << "Password for user " << targetUser << " removed successfully.\n";
            break;
        }
    }

    if (!found) {
        std::cout << "Service not found for user " << targetUser << ".\n";
    }
}
