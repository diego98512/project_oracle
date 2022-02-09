#include <iostream>
#include "globals.hpp"
#include "GameManager.hpp"

GameManager gm;

int main() {

    // Render the main menu and depending on the returned value, go to the proper screen after.
    // If return 1, player clicked Start Game.
    // If return 2, player clicked Options.
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
