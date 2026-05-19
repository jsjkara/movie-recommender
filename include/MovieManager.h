#pragma once
#include "BaseManager.h" 
#include <vector>
#include <string>    
#include "Movie.h"

class MovieManager : public BaseManager {
private:
    std::vector<Movie> movies;

public:

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override { return movies.size(); }

    void addMovie();
    void searchByTitle();
    void printAllMovies() const;
    void sortByRating();
    bool exists(int id) const;
    void updateMovieRating(int id, double score);
};