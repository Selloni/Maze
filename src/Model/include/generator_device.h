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

#ifndef A1_MAZE_1_GENERATOR_DEVICE_H_
#define A1_MAZE_1_GENERATOR_DEVICE_H_

#include "../internal/generator.h"

namespace s21 {
    /**
     *
     * GeneratorDevice class
     * Exception safety class
     * Класс поддерживает перемещение и копирование
     * Делегирует методы статического класс Generator
     *
     */
    class GeneratorDevice final {
    public:
        TRIVIAL_MOVE_COPY_CLASS(GeneratorDevice)
        
        template<FileTypes T, typename ...Parameters>
        BasicWrapper<T> Generate(const BasicGenerationSettings<T> &settings, Parameters && ...function_params) {
            BasicWrapper<T> generation;
            try {
                generation = internal::Generator<T>::Generate(settings, std::forward<Parameters>(function_params)...);
            } catch(...) {
                return {};
            }
            return generation;
        }
    };
}

#endif //A1_MAZE_1_GENERATOR_DEVICE_H_
