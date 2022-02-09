//
// Created by diego on 2/8/22.
//

#ifndef PROJECT_ORACLE_BUTTON_HPP
#define PROJECT_ORACLE_BUTTON_HPP

#include "globals.hpp"

class Button {

public:
    Rectangle ButtonRect{};
    Texture2D IdleTexture{};
    Texture2D HoverTexture{};

    Button(Rectangle buttonRect, Texture2D idleTexture, Texture2D hoverTexture) {
        ButtonRect = buttonRect;
        IdleTexture = idleTexture;
        HoverTexture = hoverTexture;
    };

    void AwaitAction(Vector2 mousePos);
};


#endif //PROJECT_ORACLE_BUTTON_HPP
