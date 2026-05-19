#include "SimilarityCalculator.h"
#include <cmath> 

double SimilarityCalculator::calculateSimilarity(const std::vector<Rating>& user1Ratings, 
                                                 const std::vector<Rating>& user2Ratings) {
    int commonCount = 0;
    double scoreDiffSum = 0.0;

    for (const auto& r1 : user1Ratings) {
        for (const auto& r2 : user2Ratings) {
            
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
                break; 
            }
        }
    }

    if (commonCount == 0) {
        return -100.0;
    }
    return (commonCount * 10) - scoreDiffSum;
}