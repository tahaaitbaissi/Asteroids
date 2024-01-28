#include "debug.h"

#include <raymath.h>
#include "raygui.h"
#include "constants.h"

static bool _showAngleCone = false;
static Vector2 line0[2];
static Vector2 line1[2];
static bool _showAstroidsCount = false;
static bool _showDebugMenu = false;
static Vector2 _playerPosition = {0};
static Vector2 _playerVelocity = {0};
static float _playerRotation = 0;


void ShowDebugMenu(void)
{
    if (IsKeyPressed(KEY_GRAVE))
    {
        _showDebugMenu = !_showDebugMenu;
    }
    if (_showDebugMenu)
        {
            Rectangle r = {10, SCREEN_HEIGHT - 40, 20, 20};
            GuiCheckBox(r, "Show Astroid Count", &_showAstroidsCount);
            r.y -= 30;
            GuiCheckBox(r, "Show Angle Cone", &_showAngleCone);
        }
}

void ShowDebugVisualizations(int astroidCount)
{
    if (_showAngleCone)
        {
            DrawLineV(line0[0], line0[1], RED);
            DrawLineV(line1[0], line1[1], BLUE);
        }
        if (_showAstroidsCount)
        {
            int count = 0;
            DrawRectangle(10, 10, 100, 52, Fade(BLACK, 0.6f));
            DrawText(TextFormat("ASTROIDS : %d", astroidCount), 20, 20, 32, WHITE);
        }
}

void SetLastCone(Vector2 position, Vector2 velocity)
{
    line0[0] = position;
        line1[0] = position;

        line0[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10), 
            -ASTROID_RANDOM_ANGLE));
        line1[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10), 
            ASTROID_RANDOM_ANGLE));
}

void SetPlayerInfo(Vector2 position, Vector2 velocity, float rotation)
{
    _playerPosition = position;
    _playerVelocity = velocity;
    _playerRotation = rotation;
}