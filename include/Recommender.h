#pragma once
#include <vector>
#include <utility>
#include "Rating.h"
#include "RatingManager.h"

class Recommender {
public:
    static int Similaritycalculate(const std::vector<Rating>& ratingsA, 
                                   const std::vector<Rating>& ratingsB);

    static std::vector<std::pair<int, double>> recommend(int targetUserId, 
                                                         const RatingManager& ratingManager, 
                                                         int k, int n);
};