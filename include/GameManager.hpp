//
// Created by diego on 2/8/22.
//
#pragma once

#ifndef PROJECT_ORACLE_GAMEMANAGER_HPP
#define PROJECT_ORACLE_GAMEMANAGER_HPP

#include "globals.hpp"

class GameManager {
public:
    const int SCREEN_WIDTH = 720;
    const int SCREEN_HEIGHT = 568;

    int RenderMenu();
    void RenderOptions();
    void StartGame();

};

#endif //PROJECT_ORACLE_GAMEMANAGER_HPP
