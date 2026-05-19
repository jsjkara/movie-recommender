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

    // 1️⃣ 단계: 대상(나) 사용자의 평점 목록 따로 모으기
    std::vector<Rating> myRatings;
    for (const auto& r : allRatings) {
        if (r.getUserId() == targetUserId) {
            myRatings.push_back(r);
        }
    }

    // 🚨 [엣지 케이스 1] 대상 사용자의 평점이 0개일 때 처리 (슬라이드 요구사항)
    if (myRatings.empty()) {
        return std::vector<std::pair<int, double>>(); // 빈 결과 반환
    }

    // 다른 유저들의 평점을 userId별로 그루핑하기 위해 map 사용
    std::map<int, std::vector<Rating>> userRatingsMap;
    for (const auto& r : allRatings) {
        if (r.getUserId() != targetUserId) {
            userRatingsMap[r.getUserId()].push_back(r);
        }
    }

    // 2️⃣ 단계: 모든 사용자와 유사도 계산 (자기 자신 제외)
    std::vector<std::pair<int, int>> similarities; // <userId, 유사도점수>
    for (const auto& pair : userRatingsMap) {
        int otherUserId = pair.first;
        const auto& otherRatings = pair.second;
        
        int simScore = Similaritycalculate(myRatings, otherRatings);
        
        // 의미 있는 유사도를 가진(공통 영화가 있었던) 유저만 후보로 등록
        if (simScore > -100) {
            similarities.push_back({otherUserId, simScore});
        }
    }

    // 🚨 [엣지 케이스 2] 유사도가 0보다 큰 사용자가 K명 미만일 때 처리
    // similarities가 비어있다면 추천할 기반이 없으므로 바로 빈 벡터 반환
    if (similarities.empty()) {
        return std::vector<std::pair<int, double>>();
    }

    // 3️⃣ 단계: 유사도 상위 K명 선택 (sort + 람다 활용)
    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // 내림차순 정렬
    });

    // 실제 활용할 이웃의 수 결정 (K명보다 적으면 있는 만큼만)
    int actualK = std::min(k, static_cast<int>(similarities.size()));

    // 4️⃣ 단계: 후보 영화 수집할 때 '내가 본 영화' 걸러내기 (set 활용)
    std::set<int> myWatchedMovieIds;
    for (const auto& r : myRatings) {
        myWatchedMovieIds.insert(r.getMovieId());
    }

    // 5️⃣ 단계: 상위 K명의 평점을 기반으로 영화별 추천 점수 누적 (map 활용)
    std::map<int, double> movieScores; // <movieId, 누적점수>
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
    
    // 점수가 높은 순으로 내림차순 정렬 (두 번째 sort + 람다 활용)
    std::sort(sortedMovies.begin(), sortedMovies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // 상위 N개만 잘라서 반환
    if (static_cast<int>(sortedMovies.size()) > n) {
        sortedMovies.resize(n);
    }

    return sortedMovies;
}