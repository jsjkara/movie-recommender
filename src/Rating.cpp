#include "Rating.h"
#include <iostream>
static constexpr double MIN_SCORE = 0.0;
static constexpr double MAX_SCORE = 5.0;
static constexpr double DEFAULT_SCORE = 0.0;

// 1. 기본 생성자
Rating::Rating() : userId(0), movieId(0), score(DEFAULT_SCORE) {}

// 2. 매개변수 생성자 
Rating::Rating(int uId, int mId, double s) 
    : userId(uId), movieId(mId) {
    
    if (s < MIN_SCORE || s > MAX_SCORE) {
        score = DEFAULT_SCORE; 
    } else {
        score = s;
    }
}

// 3. Getter 함수들
int Rating::getUserId() const { return userId; }
int Rating::getMovieId() const { return movieId; }
double Rating::getScore() const { return score; }

// 4. 자체 출력 함수 
void Rating::display() const {
    std::cout << *this << std::endl;
} 

// 5. 전역 출력 연산자 오버로딩 
std::ostream& operator<<(std::ostream& os, const Rating& r) {
    // r.userId 대신 r.getUserId()를 사용하여 캡슐화 위반 방지 및 결합도 감소
    os << "[유저 ID: " << r.getUserId() 
       << " -> 영화 ID: " << r.getMovieId() 
       << "] 평점: ★" << r.getScore();
    return os;
}