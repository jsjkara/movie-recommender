#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

void RatingManager::addRating(int userId, int movieId, double score) {
    ratings.push_back(Rating(userId, movieId, score));
    std::cout << "평점이 등록되었습니다.\n";
}

void RatingManager::printAllRatings() const {
    if (ratings.empty()) {
        std::cout << "등록된 평점이 없습니다.\n";
        return;
    }
    std::cout << "\n[ 전체 평점 기록 ]\n";
    for (const auto& r : ratings) { 
        std::cout << r << std::endl; 
    }
}

std::vector<double> RatingManager::getScoresByMovieId(int movieId) const {
    std::vector<double> scores;
    for (const auto& r : ratings) {
        if (r.getMovieId() == movieId) {
            scores.push_back(r.getScore());
        }
    }
    return scores;
}

void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;

    for (const auto& r : ratings) {
        outFile << r.getUserId() << "|" 
                << r.getMovieId() << "|" 
                << r.getScore() << std::endl;
    }
    outFile.close();
}

void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string uId_s, mId_s, score_s;

        if (std::getline(ss, uId_s, '|') &&
            std::getline(ss, mId_s, '|') &&
            std::getline(ss, score_s)) {
            addRating(std::stoi(uId_s), std::stoi(mId_s), std::stod(score_s));
        }
    }
    inFile.close();
}