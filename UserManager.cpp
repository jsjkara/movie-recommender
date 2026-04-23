#include "UserManager.h"
#include <iostream>


// 5. 사용자 추가
void UserManager::addUser() {
    int id;
    std::string name, email;
    std::cout << "사용자 ID: "; std::cin >> id;
    std::cout << "이름: "; std::cin.ignore(); std::getline(std::cin, name);
    std::cout << "이메일: "; std::getline(std::cin, email);

    users.push_back(User(id, name, email));
    std::cout << "사용자가 추가되었습니다.\n";
}

// 6. 사용자 목록 출력
void UserManager::printAllUsers() const{
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다.\n";
        return;
    }
    for (const auto& u : users) {
        std::cout << u << std::endl;
    }
}

// 사용자 존재 여부 확인
bool UserManager::exists(int id) const {
    for (const auto& u : users) {
        if (u == id) return true;
    }
    return false;
}