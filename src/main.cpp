#include <iostream>
#include <string>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h" // 1. RatingManager 헤더 추가

using namespace std;

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
    cout << "0. 프로그램 종료\n";
    cout << "===============================\n";
    cout << "선택: ";
}

int main() {
    // 2. 세 가지 매니저 객체 생성
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    // 3. 프로그램 시작 시 파일에서 데이터 로드
    movieMgr.loadFromFile("movies.txt");
    userMgr.loadFromFile("users.txt");
    ratingMgr.loadFromFile("ratings.txt");

    int choice;
    while (true) {
        printMenu();
        if (!(cin >> choice)) {
            cout << "올바른 숫자를 입력해주세요.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0) {
            // 4. 프로그램 종료 시 데이터 파일에 저장
            movieMgr.saveToFile("movies.txt");
            userMgr.saveToFile("users.txt");
            ratingMgr.saveToFile("ratings.txt");
            cout << "데이터를 저장하고 프로그램을 종료합니다.\n";
            break;
        }

        switch (choice) {
            case 1:
                movieMgr.addMovie();
                break;
            case 2:
                movieMgr.searchByTitle();
                break;
            case 3:
                // 오버로딩된 operator<와 std::sort를 이용한 평점순 출력
                movieMgr.sortByRating();
                break;
            case 4:
                userMgr.addUser();
                break;
            case 5:
                userMgr.printAllUsers();
                break;
            case 6: {
                int uId, mId;
                double score;
                cout << "사용자 ID 입력: "; cin >> uId;
                cout << "영화 ID 입력: "; cin >> mId;
                cout << "평점 입력 (0.0 ~ 5.0): "; cin >> score;

                // 5. 교차 검증 (각 매니저의 operator== 연산자 활용)
                if (!userMgr.exists(uId)) {
                    cout << "오류: 존재하지 않는 사용자 ID입니다.\n";
                } else if (!movieMgr.exists(mId)) {
                    cout << "오류: 존재하지 않는 영화 ID입니다.\n";
                } else if (score < 0.0 || score > 5.0) {
                    cout << "오류: 평점 범위를 벗어났습니다.\n";
                } else {
                    // 검증 통과 시 RatingManager에 데이터 저장
                    ratingMgr.addRating(uId, mId, score);
                    // Movie 객체 내부의 실시간 평점 정보도 업데이트
                    movieMgr.updateMovieRating(mId, score);
                }
                break;
            }
            case 7:
                // 새로 추가된 전체 평점 기록 조회 기능
                ratingMgr.printAllRatings();
                break;
            default:
                cout << "잘못된 메뉴 선택입니다. 다시 선택해주세요.\n";
                break;
        }
    }

    return 0;
}