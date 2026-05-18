#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
// 파일에 사용자 데이터 저장
void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;

    for (const auto& u : users) {
        outFile << u.getId() << "|" 
                << u.getName() << "|" 
                << u.getEmail() << std::endl;
    }
    outFile.close();
}

// 파일에서 사용자 데이터 읽어오기
void UserManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;

    users.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string id_s, name, email;

        if (std::getline(ss, id_s, '|') &&
            std::getline(ss, name, '|') &&
            std::getline(ss, email)) {
            
            int id = std::stoi(id_s);
            users.push_back(User(id, name, email));
        }
    }
    inFile.close();
}