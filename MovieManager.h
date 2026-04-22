#pragma once
#include <vector>
#include <string>
#include "Movie.h"
#include "Rating.h"

class MovieManager {
private:
    std::vector<Movie> movies; 

public:
    void addMovie();         
    void searchByTitle();    
    void printAllMovies() const; 
    void sortByRating();    
    
    // 평점 입력 시 영화가 존재하는지 확인하는 기능
    bool exists(int id) const; 
    // 평점 입력 시 해당 영화의 평균 평점을 업데이트하는 기능
    void updateMovieRating(int id, double score); 

    void showMovieRatingsWithData(const std::vector<Rating>& ratings) const;
};