#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "astroid.h"

#include "constants.h"
#include "game.h"

bool _quitGame = false;

void UpdateDrawFrame(void);

int main(void)
{
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Astroids");
    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose() && !_quitGame)
    {
        UpdateDrawFrame();
    }
    
    CloseWindow();

    return 0;
}

void UpdateDrawFrame(void)
{
    UpdateGame();

    BeginDrawing();
        ClearBackground(NEARBLACK);
        DrawGame();
    EndDrawing();
}
