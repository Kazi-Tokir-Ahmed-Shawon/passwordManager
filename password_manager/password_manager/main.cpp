// main.cpp
#include <iostream>
#include "user.h"
#include "admin.h"
#include "menu.h" // Include menu.h to use userMenu and adminMenu

int main() {
    int roleChoice;

    while (true) {
        std::cout << "\nSelect Role:\n1. User\n2. Admin\n3. Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> roleChoice;

        if (roleChoice == 1) {
            std::string username;
            std::cout << "Enter username: ";
            std::cin >> username;
            User user(username);
            userMenu(user);

        }
        else if (roleChoice == 2) {
            std::string adminUsername;
            std::cout << "Enter admin username: ";
            std::cin >> adminUsername;
            Admin admin(adminUsername);
            adminMenu(admin);

        }
        else if (roleChoice == 3) {
            std::cout << "Exiting application...\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
