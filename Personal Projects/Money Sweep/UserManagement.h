#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <unordered_map>
#include "User.h"

void registerUser(std::unordered_map<std::string, User>& users);
void login(std::unordered_map<std::string, User>& users);
void saveUserData(const std::unordered_map<std::string, User>& users);
void loadUserData(std::unordered_map<std::string, User>& users);

#endif // USER_MANAGEMENT_H
