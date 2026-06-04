#pragma once
#include <vector>
#include <utility>
#include <map>
#include "Rating.h"
#include "RatingManager.h"

class Recommender {
public:

    static int Similaritycalculate(const std::vector<Rating>& ratingsA, 
                                   const std::vector<Rating>& ratingsB);

    static std::vector<std::pair<int, double>> recommend(int targetUserId, 
                                                         const RatingManager& ratingManager, 
                                                         int k, int n);

private:
    
    static std::vector<Rating> filterTargetUserRatings(const std::vector<Rating>& allRatings, 
                                                       int targetUserId);
    
    static std::map<int, std::vector<Rating>> groupRatingsByUserId(const std::vector<Rating>& allRatings, 
                                                                   int targetUserId);
    
    static std::vector<std::pair<int, int>> getTopNeighbors(const std::vector<Rating>& myRatings, 
                                                            const std::map<int, std::vector<Rating>>& userRatingsMap, 
                                                            int k);
                                                            
    static std::vector<std::pair<int, double>> getFinalRecommendations(const std::map<int, std::vector<Rating>>& userRatingsMap,
                                                                       const std::vector<std::pair<int, int>>& topNeighbors,
                                                                       const std::vector<Rating>& myRatings, 
                                                                       int n);
};