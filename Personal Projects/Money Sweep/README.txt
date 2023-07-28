Jary Chen

*** BANK SIMULATION AND GAMBLING SYSTEM ***

-INTRODUCTION
This program is a simple command-line application that combines a user management system with a gambling game. 
The user management system allows users to register, log in, and manage their accounts, 
while the gambling game provides users with an opportunity to play a minesweeper-like game for potential winnings.

-HOW TO USE IT
All you would need is to install any IDE or text editor. However, I used 
VISUAL STUDIO CODE which is a common text editor. Link to install it:
->https://code.visualstudio.com/download

-HOW TO RUN IT
After installing and downloading the code files, you would need to path
the terminal to the file that contains the main.cpp files. By using cd.
VS Code does that for you. 
Need to run this command:
g++ *.cpp

This compiles it then you would need to run the executable:
a.exe

-USER MANAGEMENT SYSTEM USER
The user management system enables the following operations:
->Register: Users can create a new account by providing a unique username and a password. 
After registration, their account information is stored in a file named "users.txt".

->Login: Existing users can log in using their registered username and password.

->Deposit: Logged-in users can deposit money into their accounts. The amount and details 
of the deposit are recorded, and the user's balance is updated accordingly.

->Withdraw: Logged-in users can withdraw money from their account, provided they have sufficient balance.

->View Balance: Logged-in users can check their current account balance, 
view their last deposit details, and see their highest deposit amount.

-GAMBLING GAME
The gambling game is a simple luck-based game played on a grid, similar to Minesweeper. 
Users can choose the size of the game board and the number of mines to be placed on the board. 
They then have the option to gamble an amount of money to participate in the game.

During the game, users can select cells on the game board, trying to avoid hitting a mine. 
If they hit a mine, the game is over, and the gambling amount is deducted from their account
balance. However, if they choose safe cells, they can accumulate a prize amount based on 
their successful selections. Users have the option to cash out and add the current prize
amount to their account balance at any point during the game.







