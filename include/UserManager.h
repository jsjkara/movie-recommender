#pragma once
#include <vector>
#include <string>
#include "User.h"

class UserManager {
private:
    std::vector<User> users;

public:
    void addUser();
    void printAllUsers() const;
    bool exists(int id) const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};