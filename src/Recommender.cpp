#include "Recommender.h"
#include <cmath>
#include <algorithm>
#include <set>
#include <map>

static constexpr int NO_COMMON_MOVIE_ERROR = -100;
static constexpr int SIMILARITY_WEIGHT = 10;


std::vector<std::pair<int, double>> Recommender::recommend(int targetUserId, 
                                                           const RatingManager& ratingManager, 
                                                           int k, int n) {
    const std::vector<Rating>& allRatings = ratingManager.getRatings();

    // 1. 나의 평점 기록 목록 필터링
    std::vector<Rating> myRatings = filterTargetUserRatings(allRatings, targetUserId);
    if (myRatings.empty()) {
        return std::vector<std::pair<int, double>>();
    }

    // 2. 다른 유저들의 평점을 ID별로 분류 
    std::map<int, std::vector<Rating>> userRatingsMap = groupRatingsByUserId(allRatings, targetUserId);

    // 3. 나와 타인들 간의 취향 유사도 계산 및 상위 K명 이웃 엄선
    std::vector<std::pair<int, int>> topNeighbors = getTopNeighbors(myRatings, userRatingsMap, k);
    if (topNeighbors.empty()) {
        return std::vector<std::pair<int, double>>();
    }

    // 4. 엄선된 이웃들의 평점을 기반으로 추천 영화 점수 합산 후 최종 N개 추출
    return getFinalRecommendations(userRatingsMap, topNeighbors, myRatings, n);
}

// 특정 타겟 유저의 평점만 필터링
std::vector<Rating> Recommender::filterTargetUserRatings(const std::vector<Rating>& allRatings, int targetUserId) {
    std::vector<Rating> myRatings;
    for (const auto& r : allRatings) {
        if (r.getUserId() == targetUserId) {
            myRatings.push_back(r);
        }
    }
    return myRatings;
}

// 나를 제외한 타인들의 평점을 유저 ID별로 그루핑
std::map<int, std::vector<Rating>> Recommender::groupRatingsByUserId(const std::vector<Rating>& allRatings, int targetUserId) {
    std::map<int, std::vector<Rating>> userRatingsMap;
    for (const auto& r : allRatings) {
        if (r.getUserId() != targetUserId) {
            userRatingsMap[r.getUserId()].push_back(r);
        }
    }
    return userRatingsMap;
}

// 모든 사용자와의 유사도를 구하고 정렬하여 상위 K명의 이웃 목록 반환
std::vector<std::pair<int, int>> Recommender::getTopNeighbors(const std::vector<Rating>& myRatings, 
                                                              const std::map<int, std::vector<Rating>>& userRatingsMap, 
                                                              int k) {
    std::vector<std::pair<int, int>> similarities;
    
    for (const auto& pair : userRatingsMap) {
        int otherUserId = pair.first;
        const auto& otherRatings = pair.second;
        
        int simScore = Similaritycalculate(myRatings, otherRatings);
        
        if (simScore > NO_COMMON_MOVIE_ERROR) {
            similarities.push_back({otherUserId, simScore});
        }
    }

    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });

    int actualK = std::min(k, static_cast<int>(similarities.size()));
    if (actualK < static_cast<int>(similarities.size())) {
        similarities.resize(actualK);
    }

    return similarities;
}

// 이웃들의 취향을 분석하여 본인이 시청하지 않은 영화들의 최종 추천 리스트 계산
std::vector<std::pair<int, double>> Recommender::getFinalRecommendations(const std::map<int, std::vector<Rating>>& userRatingsMap,
                                                                        const std::vector<std::pair<int, int>>& topNeighbors,
                                                                        const std::vector<Rating>& myRatings, 
                                                                        int n) {
    std::set<int> myWatchedMovieIds;
    for (const auto& r : myRatings) {
        myWatchedMovieIds.insert(r.getMovieId());
    }

    std::map<int, double> movieScores; 
    for (const auto& neighbor : topNeighbors) {
        int neighborId = neighbor.first;
        const auto& neighborRatings = userRatingsMap.at(neighborId);

        for (const auto& r : neighborRatings) {
            if (myWatchedMovieIds.find(r.getMovieId()) == myWatchedMovieIds.end()) {
                movieScores[r.getMovieId()] += r.getScore();
            }
        }
    }

    std::vector<std::pair<int, double>> sortedMovies(movieScores.begin(), movieScores.end());
    std::sort(sortedMovies.begin(), sortedMovies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    if (static_cast<int>(sortedMovies.size()) > n) {
        sortedMovies.resize(n);
    }

    return sortedMovies;
}


int Recommender::Similaritycalculate(const std::vector<Rating>& ratingsA, 
                                     const std::vector<Rating>& ratingsB) {
    int commonCount = 0;
    int scoreDiffSum = 0;

    for (const auto& rA : ratingsA) {
        for (const auto& rB : ratingsB) {
            if (rA.getMovieId() == rB.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(static_cast<int>(rA.getScore() - rB.getScore()));
                break; 
            }
        }
    }

    if (commonCount == 0) {
        return NO_COMMON_MOVIE_ERROR; 
    }

    return (commonCount * SIMILARITY_WEIGHT) - scoreDiffSum;
}