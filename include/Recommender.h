#pragma once
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "Rating.h"
#include "RatingManager.h"

// MovieManager 참조를 위한 전방 선언
class MovieManager;

class Recommender {
public:
    static int Similaritycalculate(const std::vector<Rating>& ratingsA, 
                                   const std::vector<Rating>& ratingsB);

    // 🔥 movieMgr 인자 추가
    static std::vector<std::pair<int, double>> recommend(int targetUserId, 
                                                         const RatingManager& ratingManager, 
                                                         const MovieManager& movieMgr, // 👈 추가
                                                         int k, int n,
                                                         const std::string& genre = "");

private:
    static std::vector<Rating> filterTargetUserRatings(const std::vector<Rating>& allRatings, 
                                                       int targetUserId);
    
    static std::map<int, std::vector<Rating>> groupRatingsByUserId(const std::vector<Rating>& allRatings, 
                                                                   int targetUserId);
    
    static std::vector<std::pair<int, int>> getTopNeighbors(const std::vector<Rating>& myRatings, 
                                                            const std::map<int, std::vector<Rating>>& userRatingsMap, 
                                                            int k);
                                                            
    // 🔥 movieMgr 인자 추가
    static std::vector<std::pair<int, double>> getFinalRecommendations(const std::map<int, std::vector<Rating>>& userRatingsMap,
                                                                       const std::vector<std::pair<int, int>>& topNeighbors,
                                                                       const std::vector<Rating>& myRatings, 
                                                                       const MovieManager& movieMgr, // 👈 추가
                                                                       int n,
                                                                       const std::string& genre);
};