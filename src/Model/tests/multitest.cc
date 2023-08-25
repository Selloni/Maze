#include "controller.h"

s21::Controller controller;

void MultiTestCave() {
    s21::CaveGenerationSettings settings{
        .rows = 50,
        .cols = 50,
        .live_chance = 50,
        .generation_count = 5,
        .live_limit = {2, 3},
        .born_limit = {3, 3}
    };
    controller.SaveFile(controller.Generate(settings), "/Users/tonitaga/goinfre/cave#1.txt");
    auto cave = controller.ReadFile<s21::kCave>("/Users/tonitaga/goinfre/cave#1.txt");
    auto path = controller.Solve(cave, s21::Point{0, 0}, s21::Point{cave.rows - 1, cave.cols - 1});
}

void MultiTestMaze() {
    s21::MazeGenerationSettings settings {
        .rows = 50,
        .cols = 50
    };
    controller.SaveFile(controller.Generate(settings), "/Users/tonitaga/goinfre/maze#1.txt");
    auto maze = controller.ReadFile<s21::kMaze>("/Users/tonitaga/goinfre/maze#1.txt");
    auto path = controller.Solve(maze, s21::Point{0, 0}, s21::Point{maze.rows - 1, maze.cols - 1});
}

using namespace std::chrono;

int main() {
    auto begin = high_resolution_clock::now();
    for (s21::size_type test = 0; test != 1'00; ++test) {
        MultiTestCave();
        MultiTestMaze();
    }
    auto end = high_resolution_clock::now();
    std::cout << " Mean Time(ms): " << duration_cast<milliseconds>(end - begin).count() / 100.0 << std::endl;
    std::cout << "Total Time(ms): " << duration_cast<milliseconds>(end - begin).count() << std::endl;
    return 0;
}