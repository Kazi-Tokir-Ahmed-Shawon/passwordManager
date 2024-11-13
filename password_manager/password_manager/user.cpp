// user.cpp
#include "user.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>

User::User(const std::string& username) : username(username) {}

void User::storePassword(const std::string& service, const std::string& password) {
    Password newPassword(username, service, password);
    FileHandler::savePassword(newPassword);
    std::cout << "Password stored successfully.\n";
}

void User::viewPasswords() {
    auto passwords = FileHandler::loadPasswords();
    if (passwords[username].getSize() == 0) {
        std::cout << "No passwords stored.\n";
    }
    else {
        for (int i = 0; i < passwords[username].getSize(); ++i) {
            const Password& password = passwords[username][i];
            std::tm localTime;  // Create a std::tm object to store the local time

            // Use localtime_s instead of localtime
            if (localtime_s(&localTime, &password.updateDate) == 0) {
                std::cout << "Service: " << password.service
                    << ", Password: " << password.getDecryptedPassword()
                    << ", Update Date: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S")
                    << std::endl;
            }
            else {
                std::cerr << "Failed to convert update date to local time for service: "
                    << password.service << std::endl;
            }
        }

    }
}

void User::updatePassword(const std::string& service) {
    auto passwords = FileHandler::loadPasswords();
    bool found = false;

    for (int i = 0; i < passwords[username].getSize(); ++i) {
        Password& password = passwords[username][i];
        if (password.service == service) {
            found = true;
            std::string newPassword;
            std::cout << "Enter new password: ";
            std::cin >> newPassword;
            password.updatePassword(newPassword);
            FileHandler::overwritePasswords(passwords);
            std::cout << "Password updated successfully.\n";
            return;
        }
    }

    if (!found) {
        std::cout << "Service not found.\n";
    }
}

void User::deletePassword(const std::string& service) {
    auto passwords = FileHandler::loadPasswords();
    bool found = false;

    for (int i = 0; i < passwords[username].getSize(); ++i) {
        if (passwords[username][i].service == service) {
            passwords[username].remove(i);
            found = true;
            FileHandler::overwritePasswords(passwords);
            std::cout << "Password removed successfully.\n";
            break;
        }
    }

    if (!found) {
        std::cout << "Service not found.\n";
    }
}

std::string getUpdateDate(std::string username, std::string password) {
    std::string filename = "date.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::string date;
    std::getline(file, date); 
    file.close();
}
