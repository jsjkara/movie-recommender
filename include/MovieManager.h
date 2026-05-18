#pragma once
#include <vector>
#include <string>
#include "Movie.h"

class MovieManager {
private:
    std::vector<Movie> movies;

public:
    void addMovie();
    void searchByTitle();
    void printAllMovies() const;
    void sortByRating();
    bool exists(int id) const;
    void updateMovieRating(int id, double score);
    
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
