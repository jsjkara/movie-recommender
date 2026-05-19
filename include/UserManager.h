#pragma once
#include "BaseManager.h"
#include <vector>
#include <string>
#include "User.h"

class UserManager : public BaseManager { 
private:
    std::vector<User> users;

public:
   
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override { return users.size(); }

    void addUser();
    void printAllUsers() const;
    bool exists(int id) const;
};