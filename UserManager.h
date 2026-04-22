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
    
    // 평점 입력 시 사용자가 존재하는지 확인하는 기능
    bool exists(int id) const; 
};