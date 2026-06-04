#pragma once
#include <iostream>

class Rating {
public:
    // 1. 기본 생성자
    Rating();

    // 2. 매개변수 생성자 
    Rating(int uId, int mId, double s);

    // 3. Getter 함수들
    int getUserId() const;
    int getMovieId() const;
    double getScore() const;

    // 4. 자체 출력 함수
    void display() const;

private:
    int userId;
    int movieId;
    double score;
};

// 5. 전역 출력 연산자 오버로딩 
std::ostream& operator<<(std::ostream& os, const Rating& r);