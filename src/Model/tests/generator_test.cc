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
 * g++ -std=c++17 -Wall -Werror -Wextra generator_test.cc -D CAVE_GENERATION -O2 -o cave_generator
 * g++ -std=c++17 -Wall -Werror -Wextra generator_test.cc -D MAZE_GENERATION -O2 -o maze_generator
 *
 */

#include "../../Controller/controller.h"
#include <string>


#include <chrono>
#include <iostream>

using namespace std::chrono;

#ifdef CAVE_GENERATION
void TestGenerationCave(s21::Controller &controller, const s21::Controller::generator_settings<s21::kCave> &settings, const std::string &path) {
    auto begin = high_resolution_clock::now();
    controller.SaveFile<s21::kCave>(controller.Generate<s21::kCave>(settings), path);
    auto end = high_resolution_clock::now();
    std::cout << "Cave generating time(ms): " << duration_cast<milliseconds>(end - begin).count() << std::endl;
}
#endif //!CAVE_GENERATION

#ifdef MAZE_GENERATION
void TestGenerationMaze(s21::Controller &controller, const s21::Controller::generator_settings<s21::kMaze> settings, const std::string &path) {
    auto begin = high_resolution_clock::now();
    controller.SaveFile<s21::kMaze>(controller.Generate<s21::kMaze>(settings), path);
    auto end = high_resolution_clock::now();
    std::cout << "Maze generating time(ms): " << duration_cast<milliseconds>(end - begin).count() << std::endl;
}
#endif //MAZE_GENERATION


int main(int args, char *argv[]) {
    s21::Controller controller;

#ifdef CAVE_GENERATION
    if (args != 10) {
        std::cout << "We need settings for generation:\n"
                     "For example:\n"
                     "\trows cols live_chance population live_limit born_limit   save_path\n"
                     "\t 10   10     50           5         2 3       3 4       generation.txt\n";
        return -1;
    }

    s21::Controller::generator_settings<s21::kCave> settings {
        std::stoul(argv[1]),
        std::stoul(argv[2]),
        std::stoul(argv[3]),
        std::stoul(argv[4]),
        {std::stoul(argv[5]), std::stoul(argv[6])},
        {std::stoul(argv[7]), std::stoul(argv[8])}
    };

    TestGenerationCave(controller, settings, argv[9]);
#endif //!CAVE_GENERATION
#ifdef MAZE_GENERATION
    if (args != 4) {
        std::cout << "We need settings for generation:\n"
                     "For example:\n"
                     "\trows cols    save_path\n"
                     "\t 10   10   generation.txt\n";
        return -1;
    }

    s21::Controller::generator_settings<s21::kMaze> settings {
        std::stoul(argv[1]),
        std::stoul(argv[2])
    };

    TestGenerationMaze(controller, settings, argv[3]);
#endif //!MAZE_GENERATION
    return 0;
}
