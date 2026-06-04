#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <limits> 
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h" 
#include "Recommender.h" 

using namespace std;

static constexpr double MIN_RATING = 0.0;
static constexpr double MAX_RATING = 5.0;
static constexpr std::streamsize STREAM_IGNORE_MAX = std::numeric_limits<std::streamsize>::max();

// 메뉴 출력 함수
void printMenu() {
    cout << "\n===============================\n";
    cout << "   영화 추천 시스템 (V2.0)     \n";
    cout << "===============================\n";
    cout << "1. 영화 추가\n";
    cout << "2. 영화 제목 검색\n";
    cout << "3. 전체 영화 목록 출력 (평점순)\n";
    cout << "4. 사용자 추가\n";
    cout << "5. 전체 사용자 목록 출력\n";
    cout << "6. 영화 평점 입력\n";
    cout << "7. 전체 평점 기록 출력\n";
    cout << "8. 😎 개인 맞춤 영화 추천\n"; 
    cout << "0. 프로그램 종료\n";
    cout << "===============================\n";
    cout << "선택: ";
}

// [메뉴 6] 영화 평점 입력 처리 함수
void handleAddRating(MovieManager& movieMgr, UserManager& userMgr, RatingManager& ratingMgr) {
    int uId, mId;
    double score;
    cout << "사용자 ID 입력: "; cin >> uId;
    cout << "영화 ID 입력: "; cin >> mId;
    cout << "평점 입력 (" << MIN_RATING << " ~ " << MAX_RATING << "): "; cin >> score;

    if (!userMgr.exists(uId)) {
        cout << "오류: 존재하지 않는 사용자 ID입니다.\n";
    } else if (!movieMgr.exists(mId)) {
        cout << "오류: 존재하지 않는 영화 ID입니다.\n";
    } else if (score < MIN_RATING || score > MAX_RATING) {
        cout << "오류: 평점 범위를 벗어났습니다.\n";
    } else {
        ratingMgr.addRating(uId, mId, score);
        movieMgr.updateMovieRating(mId, score);
        cout << "평점이 성공적으로 등록되었습니다.\n";
    }
}

// [메뉴 8] 개인 맞춤 영화 추천 및 화면 출력 처리 함수
void handleRecommendation(const MovieManager& movieMgr, const UserManager& userMgr, const RatingManager& ratingMgr) {
    int targetUid, k, n;
    cout << "추천을 받을 사용자 ID 입력: "; cin >> targetUid;
    
    if (!userMgr.exists(targetUid)) {
        cout << "오류: 존재하지 않는 사용자 ID입니다.\n";
        return; 
    }

    cout << "비교할 이웃 수(K) 입력 (추천 2~5): "; cin >> k;
    cout << "추천받을 영화 개수(N) 입력: "; cin >> n;
    
    auto recommendations = Recommender::recommend(targetUid, ratingMgr, k, n);

    if (recommendations.empty()) {
        cout << "\nℹ️ 추천할 수 있는 영화가 없습니다.\n";
        cout << "(원인: 해당 사용자의 평점 기록이 없거나, 유사한 취향의 다른 유저가 없을 수 있습니다.)\n";
    } else {
        cout << "\n🎉 [사용자 " << targetUid << "님을 위한 맞춤 추천 영화 목록] 🎉\n";
        cout << "---------------------------------------------\n";
        int rank = 1;
        for (const auto& item : recommendations) {
            int movieId = item.first;
            double predictedScore = item.second;
            
            cout << rank << "위 | 영화 ID: " << movieId 
                 << " (추천 가중치 점수: " << predictedScore << ")\n";
            rank++;
        }
        cout << "---------------------------------------------\n";
    }
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    movieMgr.loadFromFile("data/movies.txt");
    userMgr.loadFromFile("data/users.txt");
    ratingMgr.loadFromFile("data/ratings.txt");
    movieMgr.syncRatings(ratingMgr);

    int choice;
    while (true) {
        printMenu();
        
        if (!(cin >> choice)) {
            cout << "올바른 숫자를 입력해주세요.\n";
            cin.clear();
            cin.ignore(STREAM_IGNORE_MAX, '\n'); 
            continue;
        }

        if (choice == 0) {
            movieMgr.saveToFile("data/movies.txt");
            userMgr.saveToFile("data/users.txt");
            ratingMgr.saveToFile("data/ratings.txt");
            cout << "데이터를 저장하고 프로그램을 종료합니다.\n";
            break;
        }

        switch (choice) {
            case 1:  movieMgr.addMovie();           break;
            case 2:  movieMgr.searchByTitle();      break;
            case 3:  movieMgr.sortByRating();       break;
            case 4:  userMgr.addUser();             break;
            case 5:  userMgr.printAllUsers();       break;
            case 6:  handleAddRating(movieMgr, userMgr, ratingMgr); break;
            case 7:  ratingMgr.printAllRatings();    break;
            case 8:  handleRecommendation(movieMgr, userMgr, ratingMgr); break;
            default: cout << "잘못된 메뉴 선택입니다. 다시 선택해주세요.\n"; break;
        }
    }

    return 0;
}