#include "MovieManager.h"
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
        // 기존에 수정한 operator<<가 있다면 std::cout << m << std::endl;로 변경 가능
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
        // 무결성을 위해 year 데이터도 파이프 라인에 추가합니다.
        outFile << m.getId() << "|" 
                << m.getTitle() << "|" 
                << m.getGenre() << "|" 
                << m.getReleaseYear() << std::endl; // 평점은 어차피 ratings.txt에서 복구하므로 빼는 게 안전합니다.
    }
    outFile.close();
}

// 💡 6. 파일에서 영화 데이터 읽어오기 (완벽 복원 구조)
void MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return; 

    movies.clear(); 
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string id_s, title, genre, year_s;

        // year_s를 읽어오도록 수정
        if (std::getline(ss, id_s, '|') &&
            std::getline(ss, title, '|') &&
            std::getline(ss, genre, '|') &&
            std::getline(ss, year_s)) {
            
            int id = std::stoi(id_s);
            int releaseYear = std::stoi(year_s);
            
            // 완벽한 상태의 Movie 객체 생성 후 벡터에 삽입
            movies.push_back(Movie(id, title, genre, releaseYear));
        }
    }
    inFile.close();
}