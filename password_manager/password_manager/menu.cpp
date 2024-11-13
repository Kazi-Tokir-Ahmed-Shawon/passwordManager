
#include "menu.h"
#include "user.h"
#include "admin.h"
#include "file_handler.h"
#include <iostream>
#include <unordered_map>

static bool checkUserExists(const std::unordered_map<std::string, DynamicArray<Password>>& passwords, const std::string& targetUser) {
    bool exists = passwords.find(targetUser) != passwords.end();
    if (!exists) {
        std::cout << "User " << targetUser << " does not exist.\n";
    }
    return exists;
}

static bool checkServiceExists(const std::unordered_map<std::string, DynamicArray<Password>>& passwords, const std::string& targetUser, const std::string& service) {
    if (!checkUserExists(passwords, targetUser)) return false;

    const DynamicArray<Password>& userPasswords = passwords.at(targetUser);
    for (int i = 0; i < userPasswords.getSize(); ++i) {
        if (userPasswords[i].service == service) {
            return true;
        }
    }
    std::cout << "Service " << service << " not found for user " << targetUser << ".\n";
    return false;
}

void userMenu(User& user) {
    auto passwords = FileHandler::loadPasswords();
    int choice;
    do {
        std::cout << "\nUser Menu\n";
        std::cout << "1. Store Password\n2. View Passwords\n3. Update Password\n4. Delete Password\n5. Logout\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string service, password;
            std::cout << "Enter service: ";
            std::cin >> service;
            std::cout << "Enter password: ";
            std::cin >> password;
            user.storePassword(service, password);
            break;
        }
        case 2:
            user.viewPasswords();
            break;
        case 3: {
            std::string service;
            std::cout << "Enter service to update: ";
            std::cin >> service;
            std::string uname = user.username;
            if (checkServiceExists(passwords, uname, service)) {
                user.updatePassword(service);
            }
            break;
        }
        case 4: {
            std::string service;
            std::cout << "Enter service to delete: ";
            std::cin >> service;
            if (checkServiceExists(passwords, user.username, service)) {
                user.deletePassword(service);
            }
            break;
        }
        case 5:
            std::cout << "Logging out...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}

void adminMenu(Admin& admin) {
    auto passwords = FileHandler::loadPasswords();
    int choice;
    do {
        std::cout << "\nAdmin Menu\n";
        std::cout << "1. View All Users' Passwords\n2. Update User Password\n3. Delete User Password\n4. Logout\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            admin.viewAllUsersPasswords();
            break;
        case 2: {
            std::string targetUser, service, newPassword;
            std::cout << "Enter target user: ";
            std::cin >> targetUser;
            if (checkUserExists(passwords, targetUser)) {
                std::cout << "Enter service: ";
                std::cin >> service;
                if (checkServiceExists(passwords, targetUser, service)) {
                    std::cout << "Enter new password: ";
                    std::cin >> newPassword;
                    admin.manageUserPassword(targetUser, service, newPassword);
                }
            }
            break;
        }
        case 3: {
            std::string targetUser, service;
            std::cout << "Enter target user: ";
            std::cin >> targetUser;
            if (checkUserExists(passwords, targetUser)) {
                std::cout << "Enter service: ";
                std::cin >> service;
                if (checkServiceExists(passwords, targetUser, service)) {
                    admin.deleteUserPassword(targetUser, service);
                }
            }
            break;
        }
        case 4:
            std::cout << "Logging out...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}
