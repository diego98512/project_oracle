//
// Created by diego on 2/8/22.
//

#include "Button.hpp"

void Button::AwaitAction(Vector2 mousePos) {

    if (CheckCollisionPointRec(mousePos, ButtonRect)) {
        DrawTexture(this->HoverTexture, this->ButtonRect.x, this->ButtonRect.y, WHITE);
    }
    else {
        DrawTexture(this->IdleTexture, this->ButtonRect.x, this->ButtonRect.y, WHITE);
    }
};