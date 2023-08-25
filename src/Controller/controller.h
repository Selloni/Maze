/** A1_Maze project header file
 *
 * Copyright (C) Maze Project Developers, School 21. All Rights Reserved
 *
 * If the code of this project has helped you in any way,
 * please thank us with a cup of beer.
 *
 * team-lead gmail:    gubaydullin.nurislam@gmail.com
 * team-lead telegram: @tonitaga 
 */

#ifndef A1_MAZE_1_CONTROLLER_H
#define A1_MAZE_1_CONTROLLER_H

#include "../Model/include/model.h"

namespace s21 {
    /**
     *
     */
    class Controller final {
    public:
        Controller() : model_(std::make_unique<Model>()) {}

        template<FileTypes T>
        BasicWrapper<T> ReadFile(std::string_view path) const {
            return model_->ReadFile<T>(path);
        }

        template<FileTypes T>
        bool SaveFile(const BasicWrapper<T> &data, std::string_view path) const {
            return model_->SaveFile(data, path);
        }

        template<FileTypes T, typename ...Parameters>
        BasicWrapper<T> Generate(const BasicGenerationSettings<T> &settings, Parameters &&...function_params) const {
            return model_->Generate(settings, std::forward<Parameters>(function_params)...);
        }

        template <FileTypes T, typename ...Parameters>
        std::vector<Point> Solve(const BasicWrapper<T> &data, Parameters &&...function_params) const {
            return model_->Solve(data, std::forward<Parameters>(function_params)...);
        }

    private:
        std::unique_ptr<Model> model_;
    };
}

#endif //A1_MAZE_1_CONTROLLER_H
