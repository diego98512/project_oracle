#include <iostream>
#include "globals.hpp"

int main() {

    const int screenWidth = 720;
    const int screenHeight = 568;

    bool hoverStart = false;
    bool hoverOptions = false;
    bool startButtonTextureLoaded = false;
    bool optionsButtonTextureLoaded = false;

    float volume = 0.1f;

    InitWindow(screenWidth, screenHeight, "Project Oracle");
    InitAudioDevice();

    SetTargetFPS(60);

    SetMasterVolume(volume);

    GetWorkingDirectory();

    Image projectTitleImage = LoadImage("../graphics/proj_title.png");
    Image projectTitleBackgroundImage = LoadImage("../graphics/title_background2.png");
    Image btn_options_idle = LoadImage("../graphics/btn_options_idle.png");
    Image btn_startGame_idle = LoadImage("../graphics/btn_startGame_idle.png");
    Image btn_options_hover = LoadImage("../graphics/btn_options_hover.png");
    Image btn_startGame_hover = LoadImage("../graphics/btn_startGame_hover.png");

    Texture2D projectTitleTexture = LoadTextureFromImage(projectTitleImage);
    Texture2D projectTitleBackgroundTexture = LoadTextureFromImage(projectTitleBackgroundImage);
    Texture2D btn_startGame;
    Texture2D btn_options;

    Music menuBGM = LoadMusicStream("../audio/bgm/1-02 Title Screen.mp3");

    UnloadImage(projectTitleImage);
    UnloadImage(projectTitleBackgroundImage);

    while (!WindowShouldClose()) {

        UpdateMusicStream(menuBGM);

        BeginDrawing();

        PlayMusicStream(menuBGM);

        ClearBackground(BLACK);
        DrawFPS(screenWidth - 90, screenHeight - 30);

        DrawTexture(projectTitleBackgroundTexture, screenWidth / 2 - projectTitleBackgroundTexture.width / 2, screenHeight / 2 - projectTitleBackgroundTexture.height / 2, WHITE);
        DrawTexture(projectTitleTexture, screenWidth / 2 - projectTitleTexture.width / 2, screenHeight - 80, WHITE);

        const Vector2 mouse = GetMousePosition();

        Vector2 startGamePos = {(float)screenWidth / 2 - (float)projectTitleTexture.width / 2, (float)screenHeight - 130};
        Vector2 optionsPos = {(float)screenWidth / 2 + ((float)projectTitleTexture.width / 2) - ((float)btn_options.width), (float)screenHeight - 130};

        Rectangle startGameRect = {startGamePos.x, startGamePos.y, (float)btn_startGame.width, (float)btn_startGame.height};
        Rectangle optionsRect = {optionsPos.x, optionsPos.y, (float)btn_options.width, (float)btn_options.height};

        if (!hoverStart && !startButtonTextureLoaded) {
            btn_startGame = LoadTextureFromImage(btn_startGame_idle);
            DrawTexture(btn_startGame, startGamePos.x, startGamePos.y, WHITE);
            startButtonTextureLoaded = true;
        }

        if (!hoverOptions && !optionsButtonTextureLoaded) {
            btn_options = LoadTextureFromImage(btn_options_idle);
            DrawTexture(btn_options, optionsPos.x, optionsPos.y, WHITE);
            optionsButtonTextureLoaded = true;
        }

        // If you mouse over the Start Game button:
        if (CheckCollisionPointRec(mouse, startGameRect) && startButtonTextureLoaded) {
            hoverStart = true;
            btn_startGame = LoadTextureFromImage(btn_startGame_hover);
            startButtonTextureLoaded = false;
        }

        // Otherwise, if you mouse over the Options button:
        else if (CheckCollisionPointRec(mouse, optionsRect) && optionsButtonTextureLoaded) {
            hoverOptions = true;
            btn_options = LoadTextureFromImage(btn_options_hover);
            optionsButtonTextureLoaded = false;
        }

        // If neither, they both go back to normal.
        else {
            hoverStart = false;
            hoverOptions = false;
        }

        EndDrawing();
    }

    UnloadTexture(projectTitleTexture);
    UnloadTexture(projectTitleBackgroundTexture);
    UnloadTexture(btn_options);
    UnloadTexture(btn_startGame);

    UnloadMusicStream(menuBGM);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}
