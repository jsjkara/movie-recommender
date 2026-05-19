#include "Recommender.h"
#include <cmath>
#include <algorithm>
#include <set>
#include <map>

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
        return -100;
    }

    return (commonCount * 10) - scoreDiffSum;
}

std::vector<std::pair<int, double>> Recommender::recommend(int targetUserId, 
                                                             const RatingManager& ratingManager, 
                                                             int k, int n) {
    const std::vector<Rating>& allRatings = ratingManager.getRatings();

    //  나의 평점 목록 따로 모으기
    std::vector<Rating> myRatings;
    for (const auto& r : allRatings) {
        if (r.getUserId() == targetUserId) {
            myRatings.push_back(r);
        }
    }

    if (myRatings.empty()) {
        return std::vector<std::pair<int, double>>(); 
    }

    // 다른 유저들의 평점을 userId별로 그루핑하기 위해 map 사용
    std::map<int, std::vector<Rating>> userRatingsMap;
    for (const auto& r : allRatings) {
        if (r.getUserId() != targetUserId) {
            userRatingsMap[r.getUserId()].push_back(r);
        }
    }

    // 모든 사용자와 유사도 계산 
    std::vector<std::pair<int, int>> similarities; 
    for (const auto& pair : userRatingsMap) {
        int otherUserId = pair.first;
        const auto& otherRatings = pair.second;
        
        int simScore = Similaritycalculate(myRatings, otherRatings);
        
        if (simScore > -100) {
            similarities.push_back({otherUserId, simScore});
        }
    }

    if (similarities.empty()) {
        return std::vector<std::pair<int, double>>();
    }

    // 유사도 상위 K명 선택
    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });

    // 실제 활용할 이웃의 수 결정 (K명보다 적으면 있는 만큼만)
    int actualK = std::min(k, static_cast<int>(similarities.size()));

    // 후보 영화 수집할 때 '내가 본 영화' 걸러내기 
    std::set<int> myWatchedMovieIds;
    for (const auto& r : myRatings) {
        myWatchedMovieIds.insert(r.getMovieId());
    }

    // 상위 K명의 평점을 기반으로 영화별 추천 점수 누적
    std::map<int, double> movieScores; 
    for (int i = 0; i < actualK; ++i) {
        int neighborId = similarities[i].first;
        const auto& neighborRatings = userRatingsMap[neighborId];

        for (const auto& r : neighborRatings) {
            // 내가 안 본 영화일 때만 점수 누적 후보로 등록
            if (myWatchedMovieIds.find(r.getMovieId()) == myWatchedMovieIds.end()) {
                movieScores[r.getMovieId()] += r.getScore();
            }
        }
    }

    // map의 데이터를 점수 순으로 정렬하기 위해 vector<pair>로 변환
    std::vector<std::pair<int, double>> sortedMovies(movieScores.begin(), movieScores.end());
    
    std::sort(sortedMovies.begin(), sortedMovies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    if (static_cast<int>(sortedMovies.size()) > n) {
        sortedMovies.resize(n);
    }

    return sortedMovies;
}