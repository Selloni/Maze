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

#ifndef A1_MAZE_1_FILE_MANAGER_H_
#define A1_MAZE_1_FILE_MANAGER_H_

#include "data_wrapper.h"

#include "../internal/file_reader.h"
#include "../internal/file_saver.h"

namespace s21 {
    /**
     *
     *  FileManager final class
     *  Exception safety class
     *  Класс поддерживает перемещение и копирование
     *  Делегирует методы статических классов FileReader FileSaver
     *
     */
    class FileManager final {
    public:
        TRIVIAL_MOVE_COPY_CLASS(FileManager)

        template<FileTypes T>
        BasicWrapper<T> Read(std::string_view path) {
            BasicWrapper<T> read_data;
            try {
                read_data =  internal::FileReader<T>::Read(path);
            } catch(...) {
                return {};
            }
            return read_data;
        }

        template<FileTypes T>
        bool Save(const BasicWrapper<T> &data, std::string_view path) const {
            bool result;
            try {
                result = internal::FileSaver<T>::Save(data, path);
            } catch(...) {
                return false;
            }
            return result;
        }
    };
}

#endif // !A1_MAZE_1_FILE_MANAGER_H_
