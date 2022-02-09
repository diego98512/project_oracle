//
// Created by diego on 2/8/22.
//

#include "GameManager.hpp"

int GameManager::RenderMenu() {

    bool hoverStart = false;
    bool hoverOptions = false;
    bool startButtonTextureLoaded = false;
    bool optionsButtonTextureLoaded = false;

    float volume = 0.1f;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project Oracle");
    InitAudioDevice();

    SetTargetFPS(60);

    SetMasterVolume(volume);

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
        DrawFPS(SCREEN_WIDTH - 90, SCREEN_HEIGHT - 30);

        DrawTexture(projectTitleBackgroundTexture, SCREEN_WIDTH / 2 - projectTitleBackgroundTexture.width / 2, SCREEN_HEIGHT / 2 - projectTitleBackgroundTexture.height / 2, WHITE);
        DrawTexture(projectTitleTexture, SCREEN_WIDTH / 2 - projectTitleTexture.width / 2, SCREEN_HEIGHT - 80, WHITE);

        const Vector2 mouse = GetMousePosition();

        Vector2 startGamePos = {(float)SCREEN_WIDTH / 2 - (float)projectTitleTexture.width / 2, (float)SCREEN_HEIGHT - 130};
        Vector2 optionsPos = {(float)SCREEN_WIDTH / 2 + ((float)projectTitleTexture.width / 2) - ((float)btn_options.width), (float)SCREEN_HEIGHT - 130};


        if (!startButtonTextureLoaded) {
            if (hoverStart) {
                btn_startGame = LoadTextureFromImage(btn_startGame_hover);
            }
            else {
                btn_startGame = LoadTextureFromImage(btn_startGame_idle);
            }

            DrawTexture(btn_startGame, startGamePos.x, startGamePos.y, WHITE);
            startButtonTextureLoaded = true;
        }

        if (!hoverOptions) {
            btn_options = LoadTextureFromImage(btn_options_idle);
            DrawTexture(btn_options, optionsPos.x, optionsPos.y, WHITE);
            optionsButtonTextureLoaded = true;
        }

        Rectangle startGameRect = {startGamePos.x, startGamePos.y, (float)btn_startGame.width, (float)btn_startGame.height};
        Rectangle optionsRect = {optionsPos.x, optionsPos.y, (float)btn_options.width, (float)btn_options.height};

        // If you mouse over the Start Game button:
        if (CheckCollisionPointRec(mouse, startGameRect) && startButtonTextureLoaded) {
            hoverStart = true;
            //startButtonTextureLoaded = false;
        }

            // Otherwise, if you mouse over the Options button:
        else if (CheckCollisionPointRec(mouse, optionsRect) && optionsButtonTextureLoaded) {
            hoverOptions = true;
            btn_options = LoadTextureFromImage(btn_options_hover);
            //optionsButtonTextureLoaded = false;
        }

            // If neither, they both go back to normal.
        else {
            hoverStart = false;
            hoverOptions = false;
        }

        if (IsKeyPressed(KEY_E)) {
            return 1;
        }

        if (IsKeyPressed(KEY_Q)) {
            return 2;
        }

        EndDrawing();
    }

    UnloadTexture(projectTitleTexture);
    UnloadTexture(projectTitleBackgroundTexture);
    UnloadTexture(btn_options);
    UnloadTexture(btn_startGame);
}

void GameManager::RenderOptions() {
    Music optionsBGM = LoadMusicStream("../audio/bgm/1-03 File Select.mp3");

    while (!WindowShouldClose()) {

        UpdateMusicStream(optionsBGM);

        BeginDrawing();
        ClearBackground(BLACK);

        PlayMusicStream(optionsBGM);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
}

void GameManager::StartGame() {

    Music overworldBGM = LoadMusicStream("../audio/bgm/1-07 The Overworld Theme.mp3");

    while (!WindowShouldClose()) {

        UpdateMusicStream(overworldBGM);

        BeginDrawing();
        ClearBackground(BLACK);

        PlayMusicStream(overworldBGM);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
}