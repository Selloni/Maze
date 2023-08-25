/** A1_Maze project generator.h testing file
 *
 * Copyright (C) Maze Project Developers, School 21. All Rights Reserved
 *
 * If the code of this project has helped you in any way,
 * please thank us with a cup of beer.
 *
 * team-lead gmail:    gubaydullin.nurislam@gmail.com
 * team-lead telegram: @tonitaga
 *
 * How to build:
 *
 * g++ -std=c++17 -Wall -Werror -Wextra -D CAVE_PRINT print_test.cc -o cave_print
 * g++ -std=c++17 -Wall -Werror -Wextra -D MAZE_PRINT print_test.cc -o maze_print
 *
 */

#include "../include/file_manager.h"

#include <iostream>

#ifdef MAZE_PRINT
void PrintMaze(const s21::FileManager::reading_type<s21::kMaze> &read_data) {
    std::cout << "Maze data: {rows: " << read_data.rows << ",cols: " << read_data.cols << '}' << std::endl;
    std::cout << std::string(read_data.cols * 4, '_') << std::endl;
    for (std::size_t row = 0; row != read_data.rows; ++row) {
        std::cout << '|';
        for (std::size_t col = 0; col != read_data.cols; ++col) {
            if (read_data(row, col) == 0 and read_data(row, col, false) == 0)
                std::cout << "    ";
            else if (read_data(row, col) == 1 and read_data(row, col, false) == 1)
                std::cout << "___|";
            else if (read_data(row, col) == 1 and read_data(row, col, false) == 0)
                std::cout << "   |";
            else if (read_data(row, col) == 0 and read_data(row, col, false) == 1)
                std::cout << "____";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
#endif //!MAZE_PRINT

void PrintCave(const s21::FileManager::reading_type<s21::kCave> &read_data) {
    std::cout << "Cave data: {rows: " << read_data.rows << ",cols: " << read_data.cols << '}' << std::endl;
    std::cout << std::string(read_data.cols * 2, '_') << std::endl;
    for (std::size_t row = 0; row != read_data.rows; ++row) {
        std::cout << '|';
        for (std::size_t col = 0; col != read_data.cols; ++col) {
            if (read_data(row, col) == 0)
                std::cout << "  ";
            else
                std::cout << "@ ";
        }
        std::cout << '|' << std::endl;
    }
    std::cout << std::string(read_data.cols * 2, '_') << std::endl;
    std::cout << std::endl;
}

int main(int args, char *argv[]) {
    s21::FileManager manager;
#ifdef MAZE_PRINT
    for (int arg = 1; arg != args; ++arg) {
        auto read_data = manager.Read<s21::kMaze>(argv[arg]);
        if (!read_data.IsGood()) {
            std::cerr << "Error file! Path: " << argv[arg] << std::endl;
            continue;
        }
        std::cout << "Maze path: " << argv[arg] << std::endl;
        PrintMaze(read_data);
    }
#endif //!MAZE_PRINT
#ifdef CAVE_PRINT
    for (int arg = 0; arg != args; ++arg) {
        auto read_data = manager.Read<s21::kCave>(argv[arg]);
        if (!read_data.IsGood()) {
            std::cerr << "Error file! Path: " << argv[arg] << std::endl;
            continue;
        }
        std::cout << "Cave path: " << argv[arg] << std::endl;
        PrintCave(read_data);
    }
#endif //!CAVE_PRINT
    std::getchar();
    return 0;
}
