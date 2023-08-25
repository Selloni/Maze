/** A1_Maze project file_manager.h testing file
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
 * g++ -std=c++17 -Wall -Werror -Wextra -D MAZE_READ_TEST file_manager_test.cc -o reader
 * g++ -std=c++17 -Wall -Werror -Wextra -D CAVE_READ_TEST file_manager_test.cc -o reader
 * g++ -std=c++17 -Wall -Werror -Wextra -D MAZE_SAVE_TEST file_manager_test.cc -o reader
 * g++ -std=c++17 -Wall -Werror -Wextra -D CAVE_SAVE_TEST file_manager_test.cc -o reader
 *
 */

#include "../../Controller/controller.h"

#include <iostream>
#include <chrono>

using namespace std::chrono;

s21::Controller controller;

void CaveReadTest() {
    for (auto path : {"resources/cave#1.txt", "resources/cave#2.txt", "resources/cave#3.txt", "resources/cave#4.txt"}) {
        std::cout << "=================================CAVE=READING=TEST=================================" << std::endl;
        auto begin = high_resolution_clock::now();
        const auto & read_data = controller.ReadFile<s21::kCave>(path);
        auto end = high_resolution_clock::now();
        std::cout << "Reading time is(ms): " << duration_cast<milliseconds>(end-begin).count() << std::endl;
        if (!read_data.IsGood()) {
            std::cout << "Read data is wrong! Path: " << path << std::endl;
            continue;
        } else {
            std::cout << "Read data is good! Path: " << path << std::endl;
        }
#ifdef PRINTING
        std::cout << "Read data is good! Path: " << path << std::endl;
        std::cout << "Read data size: " << read_data.data.size() << std::endl;
        std::cout << "Read data:" << std::endl;
        for (auto item : read_data.data) {
            std::cout << item << ' ';
        }
        std::cout << '\n';
#endif // !PRINTING
    }
}

void MazeReadTest() {
    for (auto path : {"resources/maze#1.txt", "resources/maze#2.txt", "resources/maze#3.txt", "resources/maze#4.txt"}) {
        std::cout << "=================================MAZE=READING=TEST=================================" << std::endl;
        auto begin = high_resolution_clock::now();
        const auto &read_data = controller.ReadFile<s21::kMaze>(path);
        auto end = high_resolution_clock::now();
        std::cout << "Reading time is(ms): " << duration_cast<milliseconds>(end-begin).count() << std::endl;
        if (!read_data.IsGood()) {
            std::cout << "Read data is wrong! Path: " << path << std::endl;
            continue;
        } else {
            std::cout << "Read data is good! Path: " << path << std::endl;
        }
#ifdef PRINTING
        std::cout << "Read data is good! Path: " << path << std::endl;
        std::cout << "Read data size: {" << read_data.data.first.size() << ',' << read_data.data.second.size() << '}' << std::endl;
        std::cout << "Read data first vector:" << std::endl;
        for (auto item : read_data.data.first) {
            std::cout << item << ' ';
        }
        std::cout << "\nRead data second vector:" << std::endl;
        for (auto item : read_data.data.second) {
            std::cout << item << ' ';
        }
        std::cout << '\n';
#endif // !PRINTING
    }
}

void CaveSaveTest() {
    std::cout << "=================================CAVE=SAVING=TEST=================================" << std::endl;
    auto begin = high_resolution_clock::now();
    const auto &read_data = controller.ReadFile<s21::kCave>("cave#1.txt");
    controller.SaveFile<s21::kCave>(read_data, "cave_saved#1.txt");
    auto end = high_resolution_clock::now();
    std::cout << "Cave saving time is(ms): " << duration_cast<milliseconds>(end-begin).count() << std::endl;
}

void MazeSaveTest() {
    std::cout << "=================================MAZE=SAVING=TEST=================================" << std::endl;
    auto begin = high_resolution_clock::now();
    const auto &read_data = controller.ReadFile<s21::kMaze>("maze#1.txt");
    controller.SaveFile<s21::kMaze>(read_data, "maze_saved#1.txt");
    auto end = high_resolution_clock::now();
    std::cout << "Maze saving time is(ms): " << duration_cast<milliseconds>(end-begin).count() << std::endl;
}


int main() {
#ifdef  CAVE_SAVE_TEST
    CaveSaveTest();
#endif // !CAVE_SAVE_TEST

#ifdef  MAZE_SAVE_TEST
    MazeSaveTest();
#endif // !MAZE_SAVE_TEST

#ifdef CAVE_READ_TEST
    CaveReadTest();
#endif // !CAVE_READ_TEST

#ifdef MAZE_READ_TEST
    MazeReadTest();
#endif // !MAZE_READ_TEST
};