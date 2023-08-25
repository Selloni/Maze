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

#ifndef A1_MAZE_1_FILE_TYPES_H_
#define A1_MAZE_1_FILE_TYPES_H_

namespace s21 {
    /**
     *
     * FileTypes enum
     * Содержит в себе константы значений,
     * которые подходят для считывания сохранения генерации решения
     *
     */
    enum FileTypes {
        kMaze = 0x7D1,
        kCave = 0x8D1
    };
}

#endif //A1_MAZE_1_FILE_TYPES_H_
