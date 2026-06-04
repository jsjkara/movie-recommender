#pragma once
#include <string>
#include <vector>
#include <utility>
#include "MovieManager.h"
#include "RatingManager.h"

class StatisticsExporter {
public:
    // 추천 결과 및 시스템 전반의 평점 통계를 CSV 파일로 내보내는 정적 메서드
    static bool exportToCSV(const std::string& filename,
                            int targetUserId,
                            const std::string& genre,
                            const std::vector<std::pair<int, double>>& recommendations,
                            const MovieManager& movieMgr,
                            const RatingManager& ratingMgr);
};