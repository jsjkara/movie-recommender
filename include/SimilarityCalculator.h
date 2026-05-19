#pragma once
#include <vector>
#include "Rating.h"

class SimilarityCalculator {
public:
    static double calculateSimilarity(const std::vector<Rating>& user1Ratings, 
                                      const std::vector<Rating>& user2Ratings);
};