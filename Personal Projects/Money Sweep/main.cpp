#include <iostream>
#include <unordered_map>
#include "User.h"
#include "UserManagement.h"
#include "GameFunctions.h"

using namespace std;

int main() {
    unordered_map<string, User> users;
    string input;

    loadUserData(users);

    while (true) {
        clearTerminal();
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        cin >> input;

        if (input == "1") {
            login(users);
        }
        else if (input == "2") {
            registerUser(users);
        }
        else if (input == "3") {
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
        cin.ignore(); // Ignore newline character left in the buffer

        cout << "Press Enter to continue...";
        cin.get(); // Wait for user input before clearing the terminal
        clearTerminal();
    }

    saveUserData(users);

    return 0;
}
