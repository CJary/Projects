#include "GameFunctions.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>
#include <map>
#include <set>
#include <random>
#include <unordered_map>
#include <cstdlib>
#include <vector>

using namespace std;

void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayBoard(const vector<vector<bool>>& gameBoard) {
    int size = gameBoard.size();

    // Print column numbers
    cout << "  ";
    for (int col = 0; col < size; col++) {
        cout << col << " ";
    }
    cout << endl;

    // Print horizontal line
    cout << " ";
    for (int col = 0; col < size; col++) {
        cout << "--";
    }
    cout << endl;

    // Print game board
    for (int row = 0; row < size; row++) {
        cout << row << "|";
        for (int col = 0; col < size; col++) {
            if (gameBoard[row][col]) {
                cout << "* ";
            }
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void deposit(User& user) {
    double amount;
    string detail;
    cout << "Enter the amount to deposit: ";
    cin >> amount;
    cin.ignore(); // Ignore newline character left in the buffer
    cout << "Enter the details of the deposit: ";
    getline(cin, detail);
    user.balance += amount;
    user.lastDepositDetail = detail;
    user.highestDeposit = max(user.highestDeposit, amount); // Track the highest deposit
    cout << "Deposit of $" << amount << " with details '" << detail << "' successful!\n";

    cout << "Press Enter to continue...";
    cin.get(); // Wait for user input before clearing the terminal
    clearTerminal();
}

void withdraw(User& user) {
    double amount;
    cout << "Enter the amount to withdraw: ";
    cin >> amount;
    if (amount > user.balance) {
        cout << "Insufficient balance.\n";
    }
    else {
        user.balance -= amount;
        cout << "Withdrawal successful!\n";
    }
    cin.ignore(); // Ignore newline character left in the buffer

    cout << "Press Enter to continue...";
    cin.get(); // Wait for user input before clearing the terminal
    clearTerminal();
}

void viewBalance(const User& user) {
    clearTerminal();
    cout << "View Balance\n";
    cout << "Balance: " << user.balance << "\n";
    cout << "Last Deposit Detail: " << user.lastDepositDetail << "\n";
    cout << "Highest Deposit: $" << user.highestDeposit << "\n";
    cin.ignore();
    cout << "Press Enter to continue...";
    cin.get();
    clearTerminal();
}

void playGamblingGame(User& user) {
    clearTerminal();
    string passwordConfirmation;
    cout << "Gambling Game\n";
    cout << "Enter your password to confirm: ";
    cin >> passwordConfirmation;

    if (passwordConfirmation == user.password) {
        clearTerminal();
        cout << "Welcome to the Gambling Game!\n";

        // Ask for the gambling amount
        int gamblingAmount;
        cout << "Enter the amount of money you want to gamble: $";
        cin >> gamblingAmount;
        cin.ignore();

        // Check if the user has enough balance
        if (gamblingAmount > user.balance) {
            cout << "Insufficient balance. Please deposit more money.\n";
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }

        // Proceed with the game
        int size;
        cout << "Enter the size of the game board (3-10): ";
        cin >> size;
        cin.ignore();

        // Check if the size is within the valid range
        if (size < 3 || size > 10) {
            cout << "Invalid size. Please try again with a size between 3 and 10.\n";
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }

        // Ask for the number of mines to place on the game board
        int numMines;
        cout << "Enter the number of mines to place (1-" << size * size - 1 << "): ";
        cin >> numMines;
        cin.ignore();

        // Check if the number of mines is within the valid range
        if (numMines < 1 || numMines > size * size - 1) {
            cout << "Invalid number of mines. Please try again with a number between 1 and " << size * size - 1 << ".\n";
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }

        vector<vector<bool>> gameBoard(size, vector<bool>(size, false));

        // Generate mines randomly on the game board
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, size - 1);
        int minesPlaced = 0;
        while (minesPlaced < numMines) {
            int row = dis(gen);
            int col = dis(gen);
            if (!gameBoard[row][col]) {
                gameBoard[row][col] = true;
                minesPlaced++;
            }
        }

        // Play the game
        vector<vector<bool>> userBoard(size, vector<bool>(size, false));
        bool gameOver = false;
        int remainingCells = size * size - numMines;
        int prizeAmount = 0; // Initialize prize amount to 0

        set<pair<int, int>> selectedPositions; // Set to record selected positions

        while (!gameOver) {
            clearTerminal();
            cout << "Gambling Game\n";
            cout << "Remaining cells: " << remainingCells << "\n";
            displayBoard(userBoard); // Visualize the board
            cout << "Prize Amount: $" << prizeAmount << "\n";
            cout << "Enter row and column (0-" << size - 1 << ") separated by a space: ";
            int row, col;
            cin >> row >> col;
            cin.ignore();

            if (row < 0 || row >= size || col < 0 || col >= size) {
                cout << "Invalid input. Please try again.\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            // Check if the position has already been selected
            if (selectedPositions.count({ row, col }) > 0) {
                cout << "Position already selected. Please choose a different position.\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            selectedPositions.insert({ row, col }); // Record the selected position

            if (gameBoard[row][col]) {
                clearTerminal();
                cout << "Gambling Game\n";
                cout << "You hit a mine! Game over!\n";
                gameOver = true;
                user.balance -= gamblingAmount; // Deduct gambling amount from balance
                prizeAmount = 0; // Reset prize amount to 0
            }
            else {
                gameBoard[row][col] = true;
                userBoard[row][col] = true;
                remainingCells--;

                // Ask if you want to cash out or continue playing
                clearTerminal();
                cout << "Gambling Game\n";
                cout << "Congratulations! You chose a safe cell!\n";
                cout << "Prize Amount: $" << prizeAmount << "\n";
                cout << "Do you want to cash out (C) or continue playing (P)? ";
                char choice;
                cin >> choice;

                if (choice == 'C' || choice == 'c') {
                    user.balance += prizeAmount; // Add the current prize amount to the balance
                    break; // Exit the game loop
                }
                else {
                    // Increment the prize amount slowly for each successful selection
                    prizeAmount += gamblingAmount / (size * size - numMines);
                }
            }

            cout << "Press Enter to continue...";
            cin.get();
        }
    }
    else {
        cout << "Password confirmation failed. Game aborted!\n";
    }
}
