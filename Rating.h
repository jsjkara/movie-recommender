#pragma once

// class Rating {
// private:
//     int userId;
//     int movieId;
//     double score;

// public:
//     Rating();
//     Rating(int uId, int mId, double s);

//     int getUserId() const;
//     int getMovieId() const;
//     double getScore() const;

//     void setScore(double s);

//     void display() const;
// };

class Rating {
private:
    int userId;
    int movieId;
    double score;

public:
    Rating();
    Rating(int uId, int mId, double s);

    
    int getUserId() const;
    int getMovieId() const;
    double getScore() const;

    
    void display() const;
};