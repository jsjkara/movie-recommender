#pragma once
#include "BaseManager.h"
#include <vector>
#include <string>
#include "Rating.h"

class RatingManager : public BaseManager { 
private:
    std::vector<Rating> ratings; 

public:
 
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override { return ratings.size(); } 

    void addRating(int userId, int movieId, double score);
    void printAllRatings() const;
    std::vector<double> getScoresByMovieId(int movieId) const;
    
    const std::vector<Rating>& getRatings() const { return ratings; }
    
};