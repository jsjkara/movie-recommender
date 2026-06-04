#pragma once
#include <string>
#include <iostream>

class Movie {
public:
    
    // 기본 생성자
    Movie();

    // 4인자 생성자 
    Movie(int id, const std::string& title, const std::string& genre, int year);
    
    // ID 비교 연산자 
    bool operator==(int targetId) const;

    // 제목 부분 일치 비교 연산자 
    bool operator==(const std::string& targetTitle) const;

    // 평점 기준 정렬을 위한 비교 연산자 오버로딩
    bool operator<(const Movie& other) const;
    bool operator>(const Movie& other) const;
    
    int getId() const;

    const std::string& getTitle() const;
    const std::string& getGenre() const;

    int getReleaseYear() const;
    int getRatingCount() const;

    // 평균 평점 계산 함수 
    double getAverageRating() const;
    
    // 새로운 평점 누적 
    void addRating(double r);

    // 자체 출력 함수 
    void display() const;

private:
    // 멤버 변수 캡슐화
    int id;
    std::string title;
    std::string genre;
    int releaseYear;
    
    double totalRating; 
    int ratingCount;    
};

// 전역 출력 연산자 오버로딩 
std::ostream& operator<<(std::ostream& os, const Movie& m);
