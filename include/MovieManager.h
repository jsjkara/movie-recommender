#pragma once
#include <vector>
#include <string>
#include "Movie.h" 

class RatingManager; 

class MovieManager {
public:
    // 1. 영화 추가
    void addMovie();
    
    // 2. 제목으로 검색 (내부적으로 입력, 필터링, 출력을 차례로 호출)
    void searchByTitle();
    
    // 3. 전체 영화 목록 출력 (내부 데이터를 순수 출력 함수로 전달)
    void printAllMovies() const;
    
    // 4. 평점순 정렬 출력 (내부적으로 정렬 후 출력 함수로 전달)
    void sortByRating();

    // 특정 영화 ID의 존재 여부 확인 
    bool exists(int id) const;
    
    // 특정 영화의 평점 실시간 갱신
    void updateMovieRating(int id, double score);
    
    // 5. 파일에 영화 데이터 저장 
    void saveToFile(const std::string& filename) const;
    
    // 6. 파일에서 영화 데이터 읽어오기
    void loadFromFile(const std::string& filename);
    
    // 평점 매니저와 영화 평점 데이터 동기화
    void syncRatings(const RatingManager& ratingMgr);

private:
    std::vector<Movie> movies;
    
    // UI: 사용자에게 검색할 제목을 콘솔로 입력받는 하위 함수
    std::string inputTargetTitle() const;

    // 로직: 순수하게 제목만 매칭하여 결과 벡터를 반환하는 필터링 함수 
    std::vector<Movie> getMoviesByTitle(const std::string& target) const;

    // 로직: 순수하게 평점순 정렬된 복사본 벡터를 반환하는 함수 (const)
    std::vector<Movie> getMoviesSortedByRating() const;

    void printMovies(const std::vector<Movie>& movieList) const;
};
