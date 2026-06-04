#include "MovieManager.h"
#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

// 1. 제목으로 검색 
void MovieManager::searchByTitle() {
    std::string target = inputTargetTitle();               
    std::vector<Movie> matched = getMoviesByTitle(target); 
    printMovies(matched);                                  
}

// 2. 평점순 정렬 출력 (목차 역할)
void MovieManager::sortByRating() {
    std::vector<Movie> sorted = getMoviesSortedByRating(); 
    printMovies(sorted);                                   
}

// 3. 전체 영화 목록 출력 (목차 역할)
void MovieManager::printAllMovies() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    std::cout << "\n[ 영화 전체 목록 ]\n";
    printMovies(movies); 
}


// 제목 필터링 구현 (Pure Logic)
std::vector<Movie> MovieManager::getMoviesByTitle(const std::string& target) const {
    std::vector<Movie> result;
    for (const auto& m : movies) {
        if (m == target) {  
            result.push_back(m);
        }
    }
    return result;
}

// 평점순 정렬 구현 (Pure Logic)
std::vector<Movie> MovieManager::getMoviesSortedByRating() const {
    std::vector<Movie> sorted = movies; 
    std::sort(sorted.begin(), sorted.end(), std::greater<Movie>()); 
    return sorted;
}

// UI: 제목 입력 전담 하위 함수
std::string MovieManager::inputTargetTitle() const {
    std::string target;
    std::cout << "검색할 제목: ";
    std::cin.ignore();
    std::getline(std::cin, target);
    return target;
}

// UI: 벡터 데이터를 받아서 순수하게 텍스트만 찍어주는 하위 함수 (재사용성 극대화)
void MovieManager::printMovies(const std::vector<Movie>& movieList) const {
    for (const auto& m : movieList) {
        std::cout << m << std::endl; 
    }
}

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

bool MovieManager::exists(int id) const {
    for (const auto& m : movies) {
        if (m == id) return true; 
    }
    return false;
}

void MovieManager::updateMovieRating(int id, double score) {
    for (auto& m : movies) {
        if (m.getId() == id) {
            m.addRating(score); 
            return;
        }
    }
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << filename << " 저장 실패!\n";
        return;
    }
    for (const auto& m : movies) {
        outFile << m.getId() << "|" << m.getTitle() << "|" << m.getGenre() << "|" << m.getReleaseYear() << std::endl;
    }
    outFile.close();
}

void MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    movies.clear();

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id_s, title, genre, year_s;

        if (std::getline(ss, id_s, '|') && std::getline(ss, title, '|') &&
            std::getline(ss, genre, '|') && std::getline(ss, year_s)) { 
            
            try {
                int id = std::stoi(id_s);
                int releaseYear = std::stoi(year_s);
                movies.push_back(Movie(id, title, genre, releaseYear));
            } 
            catch (const std::exception& e) {
                std::cerr << "⚠️ 파일 파싱 중 에러 발생 스킵: " << line << std::endl;
                continue;
            }
        }
    }
    file.close();
}

void MovieManager::syncRatings(const RatingManager& ratingMgr) {
    const std::vector<Rating>& allRatings = ratingMgr.getRatings();
    for (const auto& rating : allRatings) {
        int mId = rating.getMovieId();
        double score = rating.getScore();

        for (auto& movie : movies) {
            if (movie.getId() == mId) {
                movie.addRating(score);
                break;
            }
        }
    }
}