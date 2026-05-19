#include "MovieManager.h"
#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

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
void MovieManager::printAllMovies() const {
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
        if (m == id) return true; 
    }
    return false;
}

// 평점 데이터가 들어왔을 때 해당 영화 평점 갱신
void MovieManager::updateMovieRating(int id, double score) {
    for (auto& m : movies) {
        if (m.getId() == id) {
            m.addRating(score); 
            return;
        }
    }
}

// 💡 5. 파일에 영화 데이터 저장 (year 추가)
void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << filename << " 저장 실패!\n";
        return;
    }

    for (const auto& m : movies) {
        outFile << m.getId() << "|" 
                << m.getTitle() << "|" 
                << m.getGenre() << "|" 
                << m.getReleaseYear() << std::endl;
    }
    outFile.close();
}

// 💡 6. 파일에서 영화 데이터 읽어오기
void MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    movies.clear(); // 기존 데이터 초기화

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id_s, title, genre, year_s;

        // 💡 원래 서진님의 파일 구조인 4개 항목(파이프 3개)으로 정확히 복구합니다.
        if (std::getline(ss, id_s, '|') &&
            std::getline(ss, title, '|') &&
            std::getline(ss, genre, '|') &&
            std::getline(ss, year_s)) { // 맨 끝 항목은 뒤에 '|'를 붙이지 않습니다.
            
            int id = std::stoi(id_s);
            int releaseYear = std::stoi(year_s);

            // Movie.h 규칙에 맞는 4개짜리 생성자로 영화 객체 생성
            Movie movie(id, title, genre, releaseYear); 
            movies.push_back(movie);
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