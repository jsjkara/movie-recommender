#include <iostream>
#include <vector>
#include "MovieManager.h"
#include "UserManager.h"
#include "Rating.h"

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    std::vector<Rating> ratings; 
    int choice;

    while (true) {
        std::cout << "\n=== Movie Recommender ===\n";
        std::cout << "\n";
        std::cout << "[ 영화 ]\n";
        std::cout << "  1. 영화 추가\n";
        std::cout << "  2. 제목으로 검색\n";
        std::cout << "  3. 전체 목록 출력\n";
        std::cout << "  4. 평점순 정렬 출력\n";
        std::cout << "\n";
        std::cout << "[ 사용자 ]\n";
        std::cout << "  5. 사용자 추가\n";
        std::cout << "  6. 사용자 목록 출력\n";
        std::cout << "\n";
        std::cout << "[ 평점 ]\n";
        std::cout << "  7. 평점 입력\n";
        std::cout << "  8. 영화별 평점 보기\n";
        std::cout << "\n";
        std::cout << "  0. 종료\n";
        std::cout << "\n";
        std::cout << "선택 > ";

        // 입력 오류 방지 
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "프로그램을 종료합니다.\n";
            break;
        }

        switch (choice) {
            case 1: movieMgr.addMovie(); break;
            case 2: movieMgr.searchByTitle(); break;
            case 3: movieMgr.printAllMovies(); break;
            case 4: movieMgr.sortByRating(); break;
            case 5: userMgr.addUser(); break;
            case 6: userMgr.printAllUsers(); break;
            case 7: {
                int uId, mId;
                double score;
                std::cout << "사용자 ID: "; std::cin >> uId;
                std::cout << "영화 ID: "; std::cin >> mId;
                std::cout << "평점(0-5): "; std::cin >> score;

                if (userMgr.exists(uId) && movieMgr.exists(mId)) {
                    ratings.push_back(Rating(uId, mId, score));
                    movieMgr.updateMovieRating(mId, score); // 영화 평균 평점 갱신
                    std::cout << "평점이 성공적으로 등록되었습니다.\n";
                } else {
                    std::cout << "오류: 존재하지 않는 사용자 ID 또는 영화 ID입니다.\n";
                }
                break;
            }
            case 8: {
                
                movieMgr.showMovieRatingsWithData(ratings); 
                break;
            }
            default:
                std::cout << "존재하지 않는 메뉴입니다.\n";
                break;
        }
    }

    return 0;
}