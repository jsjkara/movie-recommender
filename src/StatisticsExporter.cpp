#include "StatisticsExporter.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>

bool StatisticsExporter::exportToCSV(const std::string& filename,
                                     int targetUserId,
                                     const std::string& genre,
                                     const std::vector<std::pair<int, double>>& recommendations,
                                     const MovieManager& movieMgr,
                                     const RatingManager& ratingMgr) {
    std::ofstream outFile(filename, std::ios::app); 
    if (!outFile.is_open()) {
        std::cerr << "❌ 오류: CSV 파일을 생성하거나 열 수 없습니다: " << filename << std::endl;
        return false;
    }

    // 1. 현재 연산 수행 시간 추출 (타임스탬프 기록용)
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");

    // 2. 만약 파일이 완전히 처음 만들어진 비어있는 상태라면 헤더(Header) 작성
    outFile.seekp(0, std::ios::end);
    if (outFile.tellp() == 0) {
        outFile << "Timestamp,TargetUserID,RequestedGenre,Rank,RecommendedMovieTitle,RecommendationScore\n";
    }

    // 3. 추천 데이터 라인별로 정밀 기록 
    int rank = 1;
    for (const auto& item : recommendations) {
        int movieId = item.first;
        double score = item.second;

        std::string movieTitle = movieMgr.getMovieTitleById(movieId);
        if (movieTitle.empty()) {
            movieTitle = "Unknown Movie";
        }

        outFile << ss.str() << ","
                << targetUserId << ","
                << (genre.empty() ? "ALL" : genre) << ","
                << rank << ",\""
                << movieTitle << "\","
                << score << "\n";
        
        rank++;
    }

    outFile.close();
    return true;
}