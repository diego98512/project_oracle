//
// Created by diego on 2/9/22.
//

#ifndef PROJECT_ORACLE_LEVEL_HPP
#define PROJECT_ORACLE_LEVEL_HPP

#include "globals.hpp"

class Level {

public:
    std::string LevelName;
    Texture2D levelMap;
    tmx_map *map;

    int LoadLevel(const char* filePath);
    static void UnloadLevel(tmx_map *map);

};

#endif //PROJECT_ORACLE_LEVEL_HPP
