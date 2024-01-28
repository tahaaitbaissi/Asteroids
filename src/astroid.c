#include "astroid.h"

#include <raymath.h>


Astroid CreateAstroid(Vector2 position, Vector2 velocity, AstroidSize size)
{
    return (Astroid)
    {
        .active = true,
        .size = size,
        .position = position,
        .rotation = GetRandomValue(0, 360),
        .rotationSpeed = GetRandomValue(ASTROID_ROT_SPEED_MIN, ASTROID_ROT_SPEED_MAX),
        .velocity = velocity,
        .creationTime = GetTime()
    };
}

bool AstroidUpdate(Astroid* astroid, float frametime, float time)
{
    if (!astroid->active)
    {
        return false;
    }

    if (time > astroid->creationTime + ASTROID_LIFE)
    {
        astroid->active = false;
        return false;
    }

    astroid->position = Vector2Add(astroid->position, 
        Vector2Scale(astroid->velocity, frametime));
    astroid->rotation += astroid->rotationSpeed * frametime;
}

void AstroidDraw(Astroid astroid)
{
    if (!astroid.active)
    {
        return;
    }
    DrawPolyLines(astroid.position, 3, AstroidRadius(astroid), astroid.rotation, WHITE);
}

float AstroidRadius(Astroid astroid)
{
    return 16.0f * (int) astroid.size;
}