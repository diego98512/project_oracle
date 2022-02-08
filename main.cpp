#include <iostream>
#include "globals.hpp"
#include "GameManager.hpp"

GameManager gm;

int main() {

    gm.RenderMenu();
    switch (gm.RenderMenu()) {
        case 1:
            gm.StartGame();
            break;
        case 2:
            gm.RenderOptions();
            break;
        default:
            return 0;
    }
    //gm.StartGame();

    //return 0;
}
