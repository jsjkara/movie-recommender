#include "Movie.h"
#include <iostream>
#include <numeric>
static constexpr double MIN_RATING = 0.0;
static constexpr double MAX_RATING = 5.0;
static constexpr double DEFAULT_RATING = 0.0;

// 기본 생성자
Movie::Movie()
    : id(0), releaseYear(0),
      totalRating(DEFAULT_RATING), ratingCount(0) {}

// 4인자 생성자
Movie::Movie(int id, const std::string& title,
             const std::string& genre, int year)
    : id(id), title(title), genre(genre),
      releaseYear(year),
      totalRating(DEFAULT_RATING), ratingCount(0) {}

bool Movie::operator==(int targetId) const {
    return this->id == targetId;
}

// 제목에 검색어가 포함되어 있는지 확인 
bool Movie::operator==(const std::string& targetTitle) const {
    return this->title.find(targetTitle) != std::string::npos;
}

// 평점 기준 정렬을 위한 비교 연산자 오버로딩
bool Movie::operator<(const Movie& other) const {
    return this->getAverageRating() < other.getAverageRating();
}

bool Movie::operator>(const Movie& other) const {
    return this->getAverageRating() > other.getAverageRating();
}

// 전역 출력 연산자 오버로딩
std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << "[ID: " << m.getId() << "] " << m.getTitle() << " (" << m.getReleaseYear() 
       << ") | 장르: " << m.getGenre() << " | 평점: " << m.getAverageRating()
       << " (" << m.getRatingCount() << "건)";
    return os;
}

int Movie::getId() const { return id; }

// 🔥 중요: 복사 생성을 막기 위해 const std::string& 로 반환 타입을 변경!
const std::string& Movie::getTitle() const { return title; }
const std::string& Movie::getGenre() const { return genre; }

int Movie::getReleaseYear() const { return releaseYear; }
int Movie::getRatingCount() const { return ratingCount; }

// 평점 평균 계산 
double Movie::getAverageRating() const {
    if (ratingCount == 0) return DEFAULT_RATING;
    return totalRating / ratingCount;
}

// 평점 누적 
void Movie::addRating(double r) {
    if (r < MIN_RATING || r > MAX_RATING) return;
    totalRating += r;
    ratingCount++;
}

void Movie::display() const {
    std::cout << *this << std::endl;
}