#include "MovieManager.h"
#include <iostream>
#include <algorithm> 
#include <string>

// 1. 영화 추가
void MovieManager::addMovie() {
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
void MovieManager::searchByTitle() {
    std::string target;
    std::cout << "검색할 제목: ";
    std::cin.ignore();
    std::getline(std::cin, target);

    for (const auto& m : movies) {
        if (m == target) {  
            std::cout << m << std::endl; 
        }
    }
}

// 3. 전체 영화 목록 출력
void MovieManager::printAllMovies() const{
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
void MovieManager::sortByRating() {
    std::vector<Movie> sorted = movies;
    
    
    std::sort(sorted.begin(), sorted.end(), std::greater<Movie>()); 

    for (const auto& m : sorted) {
        std::cout << m << std::endl; 
    }
}



// 영화 존재 여부 확인
bool MovieManager::exists(int id) const {
    for (const auto& m : movies) {
        if (m == id) return true; // operator==(int) 호출
    }
    return false;
}

// 평점 데이터가 들어왔을 때 해당 영화 평점 갱신
void MovieManager::updateMovieRating(int id, double score) {
    for (auto& m : movies) {
        if (m.getId() == id) {
            m.addRating(score); // Movie 클래스의 addRating 호출
            return;
        }
    }
}
void MovieManager::showMovieRatingsWithData(const std::vector<Rating>& ratings) const {
    if (movies.empty()) {
        std::cout << "영화 데이터가 없습니다.\n";
        return;
    }
    for (const auto& m : movies) {
        std::cout << "[" << m.getTitle() << "] 평점: ";
        bool found = false;
        for (const auto& r : ratings) {
            if (r.getMovieId() == m.getId()) {
                std::cout << r.getScore() << " ";
                found = true;
            }
        }
        if (!found) std::cout << "(평점 없음)";
        std::cout << std::endl;
    }
}