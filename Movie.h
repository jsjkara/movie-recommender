#pragma once
#include <iostream>
#include <string>
#include <vector>

class Movie {
private:
    int         id;
    std::string title;
    std::string genre;
    int         releaseYear;
    double      totalRating;    // averageRating 제거
    int         ratingCount;    // 추가
    std::vector<double> ratings;

public:
    Movie();                    // 기본 생성자 추가
    Movie(int id, const std::string& title,
          const std::string& genre, int year);

    bool operator==(int targetId) const;
    bool operator==(const std::string& targetTitle) const;
    bool operator<(const Movie& other) const;
    bool operator>(const Movie& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Movie& m);

    int         getId()              const;
    std::string getTitle()           const;
    std::string getGenre()           const;
    int         getReleaseYear()     const;  // getYear → getReleaseYear
    double      getAverageRating()   const;  // getRating → getAverageRating
    int         getRatingCount()     const;  // 추가

    void addRating(double r);               // 추가
    void display()               const;
};