#include "Manager.h"
#include <iostream>
#include <algorithm> 
#include <string>

// 1. 영화 추가
void Manager::addMovie() {
    int id, year;
    std::string title, genre;
    
    std::cout << "영화 ID: "; std::cin >> id;
    std::cout << "제목: "; std::cin.ignore(); std::getline(std::cin, title);
    std::cout << "장르: "; std::getline(std::cin, genre);
    std::cout << "개봉 연도: "; std::cin >> year;

    movies.push_back(Movie(id, title, genre, year));
    std::cout << "영화가 추가되었습니다.\n";
}

// 2. 제목으로 검색
void Manager::searchByTitle() {
    std::string target;
    std::cout << "검색할 제목 입력: ";
    std::cin.ignore();
    std::getline(std::cin, target);

    bool found = false;
    for (const auto& m : movies) {
        if (m.getTitle().find(target) != std::string::npos) {
            m.display();
            found = true;
        }
    }
    if (!found) std::cout << "검색 결과가 없습니다.\n";
}

// 3. 전체 영화 목록 출력
void Manager::printAllMovies() {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    std::cout << "\n[ 영화 전체 목록 ]\n";
    for (const auto& m : movies) {
        m.display();
    }
}

// 4. 평점순 정렬 출력 
void Manager::sortByRating() {
    if (movies.empty()) {
        std::cout << "정렬할 영화가 없습니다.\n";
        return;
    }
    // 원본 보호를 위해 복사본 생성
    std::vector<Movie> sorted = movies;
    std::sort(sorted.begin(), sorted.end(), [](const Movie& a, const Movie& b) {
        return a.getAverageRating() > b.getAverageRating(); 
    });

    std::cout << "\n[ 평점순 정렬 결과 ]\n";
    for (const auto& m : sorted) {
        m.display();
    }
}

// 5. 사용자 추가
void Manager::addUser() {
    int id;
    std::string name, email;
    std::cout << "사용자 ID: "; std::cin >> id;
    std::cout << "이름: "; std::cin.ignore(); std::getline(std::cin, name);
    std::cout << "이메일: "; std::getline(std::cin, email);

    users.push_back(User(id, name, email));
    std::cout << "사용자가 추가되었습니다.\n";
}
