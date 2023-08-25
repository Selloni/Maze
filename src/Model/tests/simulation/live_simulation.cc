#include "../../../Controller/controller.h"

void PrintCave(const s21::FileManager::reading_type<s21::kCave> &read_data) {
    static int current_generation = 1;
    for (std::size_t row = 0; row != read_data.rows; ++row) {
        for (std::size_t col = 0; col != read_data.cols; ++col) {
            if (read_data(row, col) == 0)
                printf("  ");
            else
                printf("@ ");
        }
        printf("%c", '\n');
    }
    std::cout << "Cave data: {rows: " << read_data.rows << ",cols: " << read_data.cols << ",generation: " << current_generation++ << '}' << std::endl;
}

int main(int args, char *argv[]) {
    if (args != 9) {
        std::cout << "We need settings for generation:\n"
                     "For example:\n"
                     "\trows cols live_chance population live_limit born_limit\n"
                     "\t 10   10     50           5         2 3       3 4\n";
        return -1;
    }

    auto *model = new s21::Model;
    s21::Controller controller(model);


    s21::Controller::generator_settings<s21::kCave> settings {
            std::stoul(argv[1]),
            std::stoul(argv[2]),
            std::stoul(argv[3]),
            std::stoul(argv[4]),
            {std::stoul(argv[5]), std::stoul(argv[6])},
            {std::stoul(argv[7]), std::stoul(argv[8])}
    };
    auto read_data = controller.Generate<s21::kCave>(settings);
    PrintCave(read_data);
    std::size_t generation = 0, generation_count = settings.generation_count;
    settings.generation_count = 1;
    while (generation++ != generation_count) {
        system("clear");
        controller.Generate<s21::kCave>(settings, read_data);
        PrintCave(read_data);
    }
    delete model;
    return 0;
}