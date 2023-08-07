#include "User.h"

void User::saveToFile(std::ofstream& file) const {
    file << username << ' ' << password << ' ' << balance << ' ' << lastDepositDetail << ' ' << highestDeposit << '\n';
}

void User::readFromFile(std::istream& file) {
    file >> username >> password >> balance;
    file.ignore();
    getline(file, lastDepositDetail);
    file >> highestDeposit;
}
