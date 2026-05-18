#include "User.h"
#include <iostream>

//기본생성자
User::User() 
    : id(0), name(""), email("") {}

User::User(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}

bool User::operator==(int targetId) const {
    return this->id == targetId;}

std::ostream& operator<<(std::ostream& os, const User& u) {
    os << "[User ID: " << u.id << "] 이름: " << u.name << " | 이메일: " << u.email;
    return os;
}


int         User::getId()       const { return id; }
std::string User::getName()     const { return name; }
std::string User::getEmail()    const { return email; }

void User::display() const {
    std::cout << id << ": " << name 
              << "(" << email << ")" << std::endl;
}