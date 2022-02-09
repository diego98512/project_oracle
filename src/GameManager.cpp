//
// Created by diego on 2/8/22.
//

#include "GameManager.hpp"
#include "Button.hpp"

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
    Texture2D btn_startGameIdleTexture = LoadTextureFromImage(btn_startGame_idle);
    Texture2D btn_startGameHoverTexture = LoadTextureFromImage(btn_startGame_hover);
    Texture2D btn_optionsIdleTexture = LoadTextureFromImage(btn_options_idle);
    Texture2D btn_optionsHoverTexture = LoadTextureFromImage(btn_options_hover);

    Music menuBGM = LoadMusicStream("../audio/bgm/1-02 Title Screen.mp3");

    UnloadImage(projectTitleImage);
    UnloadImage(projectTitleBackgroundImage);
    UnloadImage(btn_startGame_idle);
    UnloadImage(btn_startGame_hover);
    UnloadImage(btn_options_idle);
    UnloadImage(btn_options_hover);

    Vector2 backgroundPos = {(float)(SCREEN_WIDTH / 2 - projectTitleBackgroundTexture.width / 2), (float)(SCREEN_HEIGHT / 2 - projectTitleBackgroundTexture.height / 2)};
    Vector2 titlePos = {(float)(SCREEN_WIDTH / 2 - projectTitleTexture.width / 2),(float)(SCREEN_HEIGHT - 80)};
    Vector2 startGamePos = {(float)SCREEN_WIDTH / 2 - (float)projectTitleTexture.width / 2, (float)SCREEN_HEIGHT - 130};
    Vector2 optionsPos = {(float)SCREEN_WIDTH / 2 + ((float)projectTitleTexture.width / 2) - ((float)btn_options_idle.width), (float)SCREEN_HEIGHT - 130};

    Rectangle startGameRect = {startGamePos.x, startGamePos.y, (float)btn_startGameIdleTexture.width, (float)btn_startGameIdleTexture.height};
    Rectangle optionsRect = {optionsPos.x, optionsPos.y, (float)btn_options_idle.width, (float)btn_options_idle.height};

    Button startGame = {startGameRect, btn_startGameIdleTexture, btn_startGameHoverTexture};
    Button options = {optionsRect, btn_optionsIdleTexture, btn_optionsHoverTexture};

    BeginDrawing();
    ClearBackground(BLACK);

    while (!WindowShouldClose()) {

        DrawTexture(projectTitleBackgroundTexture, backgroundPos.x, backgroundPos.y, WHITE);
        DrawTexture(projectTitleTexture, titlePos.x, titlePos.y, WHITE);

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

    UnloadTexture(projectTitleTexture);
    UnloadTexture(projectTitleBackgroundTexture);
    UnloadTexture(btn_optionsHoverTexture);
    UnloadTexture(btn_optionsIdleTexture);
    UnloadTexture(btn_startGameHoverTexture);
    UnloadTexture(btn_startGameIdleTexture);

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