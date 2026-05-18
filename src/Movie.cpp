#include "Movie.h"
#include <iostream>
#include <numeric>

// 기본 생성자
Movie::Movie()
    : id(0), releaseYear(0),
      totalRating(0.0), ratingCount(0) {}

// 4인자 생성자
Movie::Movie(int id, const std::string& title,
             const std::string& genre, int year)
    : id(id), title(title), genre(genre),
      releaseYear(year),
      totalRating(0.0), ratingCount(0) {}


bool Movie::operator==(int targetId) const {
    return this->id == targetId;
}

bool Movie::operator==(const std::string& targetTitle) const {
    return this->title.find(targetTitle) != std::string::npos;
}

bool Movie::operator<(const Movie& other) const {
    return this->getAverageRating() < other.getAverageRating();
}

bool Movie::operator>(const Movie& other) const {
    return this->getAverageRating() > other.getAverageRating();
}

std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << "[ID: " << m.id << "] " << m.title << " (" << m.releaseYear << ") | 장르: " << m.genre 
       << " | 평점: " << m.getAverageRating();
    return os;
}

int         Movie::getId()           const { return id; }
std::string Movie::getTitle()        const { return title; }
std::string Movie::getGenre()        const { return genre; }
int         Movie::getReleaseYear()  const { return releaseYear; }
int         Movie::getRatingCount()  const { return ratingCount; }

double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;   // 0 나눗셈 방어
    return totalRating / ratingCount;
}

void Movie::addRating(double r) {
    if (r < 0.0 || r > 5.0) return;    // 유효성 검사
    totalRating += r;
    ratingCount++;
}

void Movie::display() const {           // 중복 제거 — 하나만 유지
    std::cout << id << ". " << title
              << " (" << releaseYear << ")"
              << "  평점: " << getAverageRating()
              << " (" << ratingCount << "건)"
              << std::endl;
}