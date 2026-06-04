#include "Recommender.h"
#include "MovieManager.h" // 🔥 중요: MovieManager의 함수(getMovieGenreById)를 쓰기 위해 헤더 포함
#include <cmath>
#include <algorithm>
#include <set>
#include <map>

// =================================================================
// [상수 정의] 매직 넘버 제거를 위한 constexpr 상수
// =================================================================
static constexpr int NO_COMMON_MOVIE_ERROR = -100;
static constexpr int SIMILARITY_WEIGHT = 10;

// =================================================================
// [LEVEL 1] 최상위 목차(Interface) 함수 - "장르 필터 실효성 부여"
// =================================================================

std::vector<std::pair<int, double>> Recommender::recommend(int targetUserId, 
                                                           const RatingManager& ratingManager, 
                                                           const MovieManager& movieMgr, // 🔥 movieMgr 참조 주입 완료
                                                           int k, int n,
                                                           const std::string& genre) { 
    const std::vector<Rating>& allRatings = ratingManager.getRatings();

    // 1. 나의 평점 기록 목록 필터링
    std::vector<Rating> myRatings = filterTargetUserRatings(allRatings, targetUserId);
    if (myRatings.empty()) {
        return std::vector<std::pair<int, double>>(); 
    }

    // 2. 다른 유저들의 평점을 ID별로 분류 (분리수거)
    std::map<int, std::vector<Rating>> userRatingsMap = groupRatingsByUserId(allRatings, targetUserId);

    // 3. 나와 타인들 간의 취향 유사도 계산 및 상위 K명 이웃 엄선
    std::vector<std::pair<int, int>> topNeighbors = getTopNeighbors(myRatings, userRatingsMap, k);
    if (topNeighbors.empty()) {
        return std::vector<std::pair<int, double>>();
    }

    // 4. 엄선된 이웃들의 평점을 기반으로 장르 조건까지 완벽히 검증하여 최종 N개 추출
    return getFinalRecommendations(userRatingsMap, topNeighbors, myRatings, movieMgr, n, genre); // 🔥 movieMgr 토스
}


// =================================================================
// [LEVEL 2] 중간 비즈니스 로직 함수 - "단일 책임 원칙 준수"
// =================================================================

// [책임 1] 특정 타겟 유저의 평점만 필터링
std::vector<Rating> Recommender::filterTargetUserRatings(const std::vector<Rating>& allRatings, int targetUserId) {
    std::vector<Rating> myRatings;
    for (const auto& r : allRatings) {
        if (r.getUserId() == targetUserId) {
            myRatings.push_back(r);
        }
    }
    return myRatings;
}

// [책임 2] 나를 제외한 타인들의 평점을 유저 ID별로 그루핑
std::map<int, std::vector<Rating>> Recommender::groupRatingsByUserId(const std::vector<Rating>& allRatings, int targetUserId) {
    std::map<int, std::vector<Rating>> userRatingsMap;
    for (const auto& r : allRatings) {
        if (r.getUserId() != targetUserId) {
            userRatingsMap[r.getUserId()].push_back(r);
        }
    }
    return userRatingsMap;
}

// [책임 3] 모든 사용자와의 유사도를 구하고 정렬하여 상위 K명의 이웃 목록 반환
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

    // 유사도 내림차순 정렬 (람다식)
    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });

    int actualK = std::min(k, static_cast<int>(similarities.size()));
    if (actualK < static_cast<int>(similarities.size())) {
        similarities.resize(actualK);
    }

    return similarities;
}

// [책임 4] ★장르 무력화 버그 완벽 수정 버전★ 
std::vector<std::pair<int, double>> Recommender::getFinalRecommendations(const std::map<int, std::vector<Rating>>& userRatingsMap,
                                                                        const std::vector<std::pair<int, int>>& topNeighbors,
                                                                        const std::vector<Rating>& myRatings, 
                                                                        const MovieManager& movieMgr, // 🔥 주입 완료
                                                                        int n,
                                                                        const std::string& genre) { 
    // 내가 이미 본 영화 ID 셋 구축 (탐색 복잡도 O(log N) 최적화)
    std::set<int> myWatchedMovieIds;
    for (const auto& r : myRatings) {
        myWatchedMovieIds.insert(r.getMovieId());
    }

    // 이웃들이 평가한 영화 점수 합산
    std::map<int, double> movieScores; 
    for (const auto& neighbor : topNeighbors) {
        int neighborId = neighbor.first;
        const auto& neighborRatings = userRatingsMap.at(neighborId);

        // 슬라이드 3 지침: 대용량 복사 방지 const auto& 및 range-for 활용
        for (const auto& r : neighborRatings) {
            int mId = r.getMovieId();

            // 1차 검증: 내가 안 본 영화인지 확인
            if (myWatchedMovieIds.find(mId) == myWatchedMovieIds.end()) {
                
                // 2차 검증: 사용자가 특정 장르를 지정하여 필터링을 원할 때
                if (!genre.empty()) {
                    // MovieManager에게 이 영화 ID의 진짜 장르가 뭔지 실시간 대조 요청
                    if (movieMgr.getMovieGenreById(mId) != genre) {
                        continue; // 💥 입력한 장르와 매칭되지 않으면 누적하지 않고 다음 영화로 Skip!
                    }
                }
                
                movieScores[mId] += r.getScore();
            }
        }
    }

    // 점수 정렬 및 상위 N개 리사이징
    std::vector<std::pair<int, double>> sortedMovies(movieScores.begin(), movieScores.end());
    std::sort(sortedMovies.begin(), sortedMovies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    if (static_cast<int>(sortedMovies.size()) > n) {
        sortedMovies.resize(n);
    }

    return sortedMovies;
}


// =================================================================
// [LEVEL 3] 하위 연산 함수 - "순수 수학적 계산 연산 전담"
// =================================================================

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