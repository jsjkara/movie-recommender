#include "Manager.h"
#include <iostream>

int main() {
    Manager manager;
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
            case 1: manager.addMovie(); break;
            case 2: manager.searchByTitle(); break;
            case 3: manager.printAllMovies(); break;
            case 4: manager.sortByRating(); break;
            case 5: manager.addUser(); break;
            case 6: manager.printAllUsers(); break;
            case 7: manager.addRating(); break;
            case 8: manager.showMovieRatings(); break;
            default:
                std::cout << "존재하지 않는 메뉴입니다.\n";
                break;
        }
    }

    return 0;
}