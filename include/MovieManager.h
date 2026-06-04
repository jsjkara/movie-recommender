#pragma once
#include <vector>
#include <string>
#include "Movie.h" // Movie 클래스 정의가 포함된 헤더

// RatingManager의 순환 참조(Circular Dependency)를 방지하기 위한 전방 선언
class RatingManager; 

class MovieManager {
public:
    // =================================================================
    // [LEVEL 1] 최상위 인터페이스 메서드 (main에서 직접 호출하는 기능들)
    // =================================================================
    
    // 1. 영화 추가
    void addMovie();
    
    // 2. 제목으로 검색 (내부적으로 입력, 필터링, 출력을 차례로 호출)
    void searchByTitle();
    
    // 3. 전체 영화 목록 출력 (내부 데이터를 순수 출력 함수로 전달)
    void printAllMovies() const;
    
    // 4. 평점순 정렬 출력 (내부적으로 정렬 후 출력 함수로 전달)
    void sortByRating();

    // =================================================================
    // [데이터 관리 및 동기화 메서드]
    // =================================================================
    
    // 특정 영화 ID의 존재 여부 확인 (조회용이므로 const)
    bool exists(int id) const;
    
    // 특정 영화의 평점 실시간 갱신
    void updateMovieRating(int id, double score);
    
    // 5. 파일에 영화 데이터 저장 (내부 데이터를 바꾸지 않으므로 const)
    void saveToFile(const std::string& filename) const;
    
    // 6. 파일에서 영화 데이터 읽어오기
    void loadFromFile(const std::string& filename);
    
    // 평점 매니저와 영화 평점 데이터 동기화
    void syncRatings(const RatingManager& ratingMgr);

    // 🔥 [새로 추가된 핵심 헬퍼] 영화 ID로 제목 찾기 (main.cpp 8번 메뉴 연동)
    std::string getMovieTitleById(int id) const;

    // 🔥 [새로 추가된 핵심 헬퍼] 영화 ID로 장르 찾기 (Recommender 엔진 연동)
    std::string getMovieGenreById(int id) const;

    // 장르 기준 필터링 함수 (기능확장용)
    std::vector<Movie> filterByGenre(const std::vector<Movie>& candidates, const std::string& genre) const;

private:
    // 멤버 변수: 영화 객체들을 담는 벡터 창고
    std::vector<Movie> movies;

    // =================================================================
    // [LEVEL 2 & 3] 하위 구현 메서드 (단일 책임 원칙을 위해 내부 캡슐화)
    // =================================================================
    
    // UI: 사용자에게 검색할 제목을 콘솔로 입력받는 하위 함수
    std::string inputTargetTitle() const;

    // 로직: 순수하게 제목만 매칭하여 결과 벡터를 반환하는 필터링 함수 (const)
    std::vector<Movie> getMoviesByTitle(const std::string& target) const;

    // 로직: 순수하게 평점순 정렬된 복사본 벡터를 반환하는 함수 (const)
    std::vector<Movie> getMoviesSortedByRating() const;

    // UI: 전달받은 영화 벡터 리스트를 순수하게 화면에 출력만 하는 함수 (재사용성 극대화)
    // 체크리스트 기준: 큰 객체(vector)이므로 무조건 'const std::vector<Movie>&'로 받음
    void printMovies(const std::vector<Movie>& movieList) const;
};
