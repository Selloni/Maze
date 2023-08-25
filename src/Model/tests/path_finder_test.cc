#include "controller.h"

void MazePathFindTest(s21::Controller &controller) {
    s21::MazeGenerationSettings settings {25, 25};
    s21::MazeWrapper maze = controller.Generate(settings);
    if (!maze.IsGood()) {
        std::cout << "Generated maze is wrong!" << std::endl;
        return;
    }

    auto path = controller.Solve(maze, s21::Point{0, 0}, s21::Point{maze.rows - 1, maze.cols - 1});

    auto is_there = [&path](std::size_t x, std::size_t y) {
        for (auto [row, col] : path) {
            if (row == x and col == y)
                return true;
        }
        return false;
    };

    std::cout << "\n\x1b[31mMAZE PATH SHOW\x1b[0m\n" << std::endl;
    for (int i = 0; i != maze.rows; ++i) {
        for (int j = 0; j != maze.cols; ++j) {
            if (is_there(i, j))
                std::cout << "\x1b[31m @ \x1b[0m";
            else
                std::cout << " @ ";
        }
        std::cout << '\n';
    }
}

void CavePathFindTest(s21::Controller &controller) {
    s21::CaveGenerationSettings settings {25, 25, 40, 10, {2, 3}, {3, 3}};
    s21::CaveWrapper cave = controller.Generate(settings);
    if (!cave.IsGood()) {
        std::cout << "Generated cave is wrong!" << std::endl;
        return;
    }

    auto path = controller.Solve(cave, s21::Point{0, 0}, s21::Point{cave.rows - 1, cave.cols - 1});

    auto is_there = [&path](std::size_t x, std::size_t y) {
        for (auto [row, col] : path) {
            if (row == x and col == y)
                return true;
        }
        return false;
    };

    std::cout << "\n\x1b[31mCAVE PATH SHOW\x1b[0m\n" << std::endl;
    for (int i = 0; i != cave.rows; ++i) {
        for (int j = 0; j != cave.cols; ++j) {
            if (is_there(i, j)) {
                if (cave(i, j) == 0) {
                    std::cout << "\x1b[31m . \x1b[0m";
                } else {
                    std::cout << "\x1b[31m @ \x1b[0m";
                }

            } else if (cave(i, j) == 0) {
                std::cout << " . ";
            } else if (cave(i, j) == 1) {
                std::cout << " @ ";
            }
        }
        std::cout << '\n';
    }
}


int main() {
    s21::Controller controller;
    MazePathFindTest(controller);
    CavePathFindTest(controller);
}
