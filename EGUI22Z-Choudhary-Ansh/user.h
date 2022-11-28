#ifndef USER_H
#define USER_H

#include <json.hpp> // https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp
#include <iostream>

typedef struct {
    std::string user;
    std::string pwd;
} User;

void from_json(const nlohmann::json& j, User& p);
void to_json(nlohmann::json& j, const User& p);
std::vector<User> fetchUsers();
void writeUsers(std::vector<User>& user);

#endif // USER_H
