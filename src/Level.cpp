//
// Created by diego on 2/9/22.
//

#include "Level.hpp"
#include "Rendering.hpp"

int Level::LoadLevel(const char *filePath) {

    this->map = tmx_load(filePath);
    if (!map) {
        tmx_perror("Cannot load map");
        return 1;
    }

    render_map(map);
    return 0;
}

void Level::UnloadLevel(tmx_map *map) {
    tmx_map_free(map);
}