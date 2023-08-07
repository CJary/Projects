#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <vector>

void clearTerminal();
void displayBoard(const std::vector<std::vector<bool>>& gameBoard);
void deposit(User& user);
void withdraw(User& user);
void viewBalance(const User& user);
void playGamblingGame(User& user);

#endif // GAME_FUNCTIONS_H
