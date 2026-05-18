#include "Rating.h"
#include <iostream>

// 1. 기본 생성자
Rating::Rating() : userId(0), movieId(0), score(0.0) {}

// 2. 매개변수 생성자 (방어적 설계 적용)
Rating::Rating(int uId, int mId, double s) 
    : userId(uId), movieId(mId) {
    
    if (s < 0.0 || s > 5.0) score = 0.0; 
    else score = s;
}

// 3. Getter 함수들
int Rating::getUserId() const { return userId; }
int Rating::getMovieId() const { return movieId; }
double Rating::getScore() const { return score; }

// 4. 자체 출력 함수
void Rating::display() const {
    std::cout << userId << ". " << movieId 
              << " (" << score << "점)" << std::endl;
} // 💡 원래 여기가 뚫려있어서 에러가 났던 부분을 정확히 닫아주었습니다!

// 5. 전역 출력 연산자 오버로딩 (friend 함수 구현)
// ⚠️ 주의: 구현부(.cpp)에서는 'friend' 키워드를 붙이지 않고 함수 이름만 적습니다.
std::ostream& operator<<(std::ostream& os, const Rating& r) {
    os << "[유저 ID: " << r.userId << " -> 영화 ID: " << r.movieId << "] 평점: ★" << r.score;
    return os;
}