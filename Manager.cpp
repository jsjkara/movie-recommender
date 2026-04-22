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

// 6. 사용자 목록 출력
void Manager::printAllUsers() {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다.\n";
        return;
    }
    for (const auto& u : users) {
        u.display();
    }
}

// 7. 평점 입력
void Manager::addRating() {
    int uId, mId;
    double score;
    std::cout << "사용자 ID: "; std::cin >> uId;
    std::cout << "영화 ID: "; std::cin >> mId;
    std::cout << "평점(0~5): "; std::cin >> score;

    // 1. Rating 객체 저장
    ratings.push_back(Rating(uId, mId, score));

    // 2. 실제 Movie 객체에 평점 반영 (평점 평균 업데이트를 위해)
    for (auto& m : movies) {
        if (m.getId() == mId) {
            m.addRating(score);
            std::cout << "평점이 반영되었습니다.\n";
            return;
        }
    }
    std::cout << "해당 ID의 영화를 찾을 수 없습니다.\n";
}

// 8. 영화별 전체 평점 목록 조회
void Manager::showMovieRatings() {
    if (movies.empty()) {
        std::cout << "영화 데이터가 없습니다.\n";
        return;
    }
    for (const auto& m : movies) {
        std::cout << "[" << m.getTitle() << "] 평점 목록: ";
        bool hasRating = false;
        for (const auto& r : ratings) {
            if (r.getMovieId() == m.getId()) {
                std::cout << r.getScore() << " ";
                hasRating = true;
            }
        }
        if (!hasRating) std::cout << "(평점 없음)";
        std::cout << std::endl;
    }
}