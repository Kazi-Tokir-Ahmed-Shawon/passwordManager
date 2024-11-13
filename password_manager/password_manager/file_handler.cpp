// file_handler.cpp
#include "file_handler.h"
#include <fstream>
#include <iostream>  // Optional, for debug purposes

void FileHandler::savePassword(const Password& password) {
    std::ofstream file("passwords.txt", std::ios::app);
    if (!file) {
        std::cerr << "Error opening passwords.txt for writing.\n";
        return;
    }

    file << password.username << " " << password.service << " "
        << password.encryptedPassword << " " << password.createDate << " "
        << password.updateDate << std::endl;

    file.close();
}

std::unordered_map<std::string, DynamicArray<Password>> FileHandler::loadPasswords() {
    std::unordered_map<std::string, DynamicArray<Password>> passwords;
    std::ifstream file("passwords.txt");

    if (!file) {
        std::cerr << "Failed to open passwords.txt" << std::endl;
        return passwords; // Return empty map if file open fails
    }

    std::string u, s, p;
    time_t c, uDate;

    while (file >> u >> s >> p >> c >> uDate) {
        Password pass(u, s, Encryptor::decrypt(p));
        pass.createDate = c;
        pass.updateDate = uDate;
        passwords[u].push_back(pass);
    }
    file.close();
    return passwords;
}

void FileHandler::overwritePasswords(const std::unordered_map<std::string, DynamicArray<Password>>& passwords) {
    std::ofstream file("passwords.txt", std::ios::trunc);  // Open file in truncate mode to overwrite

    for (const auto& pair : passwords) {
        const std::string& user = pair.first;
        const DynamicArray<Password>& userPasswords = pair.second;

        for (int i = 0; i < userPasswords.getSize(); ++i) {
            const Password& password = userPasswords[i];
            file << password.username << " " << password.service << " "
                << password.encryptedPassword << " " << password.createDate << " "
                << password.updateDate << std::endl;
        }
    }
    file.close();
}
