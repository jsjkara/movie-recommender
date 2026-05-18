#pragma once
#include <vector>
#include <string>
#include "Rating.h"

class RatingManager {
private:
    std::vector<Rating> ratings; 

public:
    
    void addRating(int userId, int movieId, double score);
    
    void printAllRatings() const;

    std::vector<double> getScoresByMovieId(int movieId) const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    const std::vector<Rating>& getRatings() const { return ratings; }
};