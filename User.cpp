#include "User.h"
#include <iostream>

//기본생성자
User::User() 
    : id(0), name(""), email("") {}

User::User(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}

int         User::getId()       const { return id; }
std::string User::getName()     const { return name; }
std::string User::getEmail()    const { return email; }

void User::display() const {
    std::cout << id << ": " << name 
              << "(" << email << ")" << std::endl;
}