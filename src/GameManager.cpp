//
// Created by diego on 2/8/22.
//

#include "GameManager.hpp"
#include "Button.hpp"
#include "Level.hpp"

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

    Image projTitleImg = LoadImage("../graphics/proj_title.png");
    Image projTitleBGImg = LoadImage("../graphics/title_background2.png");
    Image btn_options_idle = LoadImage("../graphics/btn_options_idle.png");
    Image btn_startGame_idle = LoadImage("../graphics/btn_startGame_idle.png");
    Image btn_options_hover = LoadImage("../graphics/btn_options_hover.png");
    Image btn_startGame_hover = LoadImage("../graphics/btn_startGame_hover.png");

    Texture2D projTitleTex = LoadTextureFromImage(projTitleImg);
    Texture2D projTitleBGTex = LoadTextureFromImage(projTitleBGImg);
    Texture2D btn_startGameIdleTex = LoadTextureFromImage(btn_startGame_idle);
    Texture2D btn_startGameHoverTex = LoadTextureFromImage(btn_startGame_hover);
    Texture2D btn_optionsIdleTex = LoadTextureFromImage(btn_options_idle);
    Texture2D btn_optionsHoverTex = LoadTextureFromImage(btn_options_hover);

    Music menuBGM = LoadMusicStream("../audio/bgm/1-02 Title Screen.mp3");

    UnloadImage(projTitleImg);
    UnloadImage(projTitleBGImg);
    UnloadImage(btn_startGame_idle);
    UnloadImage(btn_startGame_hover);
    UnloadImage(btn_options_idle);
    UnloadImage(btn_options_hover);

    Vector2 backgroundPos = {(float)(SCREEN_WIDTH / 2 - projTitleBGTex.width / 2), (float)(SCREEN_HEIGHT / 2 - projTitleBGTex.height / 2)};
    Vector2 titlePos = {(float)(SCREEN_WIDTH / 2 - projTitleTex.width / 2), (float)(SCREEN_HEIGHT - 80)};
    Vector2 startGamePos = {(float)SCREEN_WIDTH / 2 - (float)projTitleTex.width / 2, (float)SCREEN_HEIGHT - 130};
    Vector2 optionsPos = {(float)SCREEN_WIDTH / 2 + ((float)projTitleTex.width / 2) - ((float)btn_options_idle.width), (float)SCREEN_HEIGHT - 130};

    Rectangle startGameRect = {startGamePos.x, startGamePos.y, (float)btn_startGameIdleTex.width, (float)btn_startGameIdleTex.height};
    Rectangle optionsRect = {optionsPos.x, optionsPos.y, (float)btn_options_idle.width, (float)btn_options_idle.height};

    Button startGame = {startGameRect, btn_startGameIdleTex, btn_startGameHoverTex};
    Button options = {optionsRect, btn_optionsIdleTex, btn_optionsHoverTex};

    tmx_map *HV_Spring = tmx_load("../graphics/tilemaps/HV_Spring.tmx");

    if (HV_Spring == nullptr) {
        tmx_perror("Cannot load HV_Spring.");
        return 3;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    while (!WindowShouldClose()) {

        DrawTexture(projTitleBGTex, backgroundPos.x, backgroundPos.y, WHITE);
        DrawTexture(projTitleTex, titlePos.x, titlePos.y, WHITE);

        UpdateMusicStream(menuBGM);

        PlayMusicStream(menuBGM);

        DrawFPS(SCREEN_WIDTH - 90, SCREEN_HEIGHT - 30);

        const Vector2 mouse = GetMousePosition();

        startGame.AwaitAction(mouse);
        options.AwaitAction(mouse);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(mouse, startGameRect)) {
                return 1;
            }

            if (CheckCollisionPointRec(mouse, optionsRect)) {
                return 2;
            }
        }

        EndDrawing();
    }

    UnloadTexture(projTitleTex);
    UnloadTexture(projTitleBGTex);
    UnloadTexture(btn_optionsHoverTex);
    UnloadTexture(btn_optionsIdleTex);
    UnloadTexture(btn_startGameHoverTex);
    UnloadTexture(btn_startGameIdleTex);

    return 0;
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

    Music overworldBGM = LoadMusicStream("../audio/bgm/1-14 Level 1, Gnarled Root Dungeon (Aquamentus).mp3");
    Level HV_Spring;

    while (!WindowShouldClose()) {

        UpdateMusicStream(overworldBGM);

        BeginDrawing();
        ClearBackground(BLACK);

        HV_Spring.LoadLevel("../graphics/tilemaps/HV_Spring.tmx");


        PlayMusicStream(overworldBGM);

        EndDrawing();
    }

    HV_Spring.UnloadLevel(HV_Spring.map);
    CloseAudioDevice();
    CloseWindow();
}