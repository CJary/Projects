#ifndef USER_H
#define USER_H

#include <fstream>
#include <string>

class User {
public:
    std::string username;
    std::string password;
    double balance;
    std::string lastDepositDetail;
    double highestDeposit;

    void saveToFile(std::ofstream& file) const;
    void readFromFile(std::istream& file);
};

#endif // USER_H
