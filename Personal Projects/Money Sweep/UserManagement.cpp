#include "UserManagement.h"
#include <iostream>
#include <fstream>

void registerUser(std::unordered_map<std::string, User>& users) {
    clearTerminal();
    string username, password;
    cout << "Create User\n";
    cout << "Enter username: ";
    cin >> username;

    // Check if username already exists
    if (users.find(username) != users.end()) {
        cout << "Username already exists. Please try again.\n";
        cout << "\n\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Create a new User object and store it in the unordered_map
    User newUser;
    newUser.username = username;
    newUser.password = password;
    newUser.balance = 0.0;
    newUser.highestDeposit = 0.0;
    users[username] = newUser;

    cout << "Registration successful!\n";
    cout << "\n\n";
    cin.ignore(); // Ignore newline character left in the buffer

    cout << "Press Enter to continue...";
    cin.get(); // Wait for user input before clearing the terminal
    clearTerminal();
}

void login(std::unordered_map<std::string, User>& users) {
    clearTerminal();
    string username, password;
    cout << "Login\n";
    cout << "Enter username: ";
    cin >> username;

    // Check if the username exists in the unordered_map
    if (users.find(username) == users.end()) {
        cout << "Invalid username. Please try again.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Check if the password matches
    if (users[username].password != password) {
        cout << "Incorrect password. Please try again.\n";
        return;
    }

    cout << "Login successful!\n";
    cin.ignore(); // Ignore newline character left in the buffer

    cout << "Press Enter to continue...";
    clearTerminal();

    // Proceed with the logged-in user operations
    string input;
    while (true) {
        clearTerminal();
        cout << "Logged-in User Operations for " << users[username].username << "\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. View Balance\n";
        cout << "4. Play Gambling Game\n";
        cout << "5. Back\n";
        cout << "Enter your choice: ";
        cin >> input;

        if (input == "1") {
            deposit(users[username]);
        }
        else if (input == "2") {
            withdraw(users[username]);
        }
        else if (input == "3") {
            viewBalance(users[username]);
        }
        else if (input == "4") {
            playGamblingGame(users[username]);
        }
        else if (input == "5") {
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
        clearTerminal();
    }
}

void saveUserData(const std::unordered_map<std::string, User>& users) {
    ofstream outFile("users.txt");

    // Write user data to file before program ends
    if (outFile.is_open()) {
        for (const auto& userPair : users) {
            userPair.second.saveToFile(outFile);
        }
        outFile.close();
    }
}

void loadUserData(std::unordered_map<std::string, User>& users) {
    ifstream inFile("users.txt");

    // Read user data from file and populate the map
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            istringstream iss(line);
            User user;
            user.readFromFile(iss);
            users[user.username] = user;
        }
        inFile.close();
    }
}
