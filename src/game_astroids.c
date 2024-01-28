#include "game_astroids.h"
#include <raymath.h>

#include "constants.h"
#include "debug.h"
#include "game_score.h"

static Astroid _astroids[MAX_ASTROIDS] = {0};
static AstroidSize _sizes[] = {
    ASTROID_SMALL,
    ASTROID_MEDIUM,
    ASTROID_LARGE
};
static float _lastAstroidCreationTime = -1.0f;

void AddAstroid(Vector2 position, AstroidSize size, float speedMod, bool spawn)
{
    int i;
    bool created = false;
    Vector2 velocity = spawn
        ? Vector2Subtract(SCREEN_CENTER, position)
        : Vector2Rotate((Vector2) {0, 1}, (float) GetRandomValue(0, 359));
    
    velocity = Vector2Scale(Vector2Normalize(velocity), GetRandomValue(
        ASTROID_SPEED_MIN, ASTROID_SPEED_MAX) * speedMod);

    SetLastCone(position, velocity);

    for (i = 0; i < MAX_ASTROIDS; i++)
    {
        if (_astroids[i].active)
        {
            continue;
        }

        _astroids[i] = CreateAstroid(position, velocity, size);
        created = true;
        break;
    }
    
    if (!created)
    {
        TraceLog(LOG_ERROR, "Failed to create an astroid because there was no inactive spots in the array.");
    }
}

Vector2 GetNextAstroidPosition(void)
{
    int padding = 128;
    Vector2 result = {-padding, -padding};
    if (GetRandomValue(0, 1))
    {
        if (GetRandomValue(0, 1))
        {
            result.y = SCREEN_HEIGHT + padding;
        }
        result.x = GetRandomValue(-padding, SCREEN_WIDTH + padding);
    }
    else
    {
        if (GetRandomValue(0, 1))
        {
            result.x = SCREEN_WIDTH + padding;
        }
        result.y = GetRandomValue(-padding, SCREEN_HEIGHT + padding);
    }
    return result;
}

int UpdateAstroids(void)
{
    int i, activeAstroids = 0;
    float frametime = GetFrameTime();
    float time = GetTime();

    for (i = 0; i < MAX_ASTROIDS; i++)
    {
        if(AstroidUpdate(_astroids + i, frametime, time))
        {
            activeAstroids++;
        }
    }

    if (time > _lastAstroidCreationTime + ASTROID_DELAY)
    {
        AstroidSize nextSize;
        nextSize = _sizes[GetRandomValue(0, 2)];
        AddAstroid(GetNextAstroidPosition(), nextSize, 1.0f, true);
        _lastAstroidCreationTime = time;
    }
    return activeAstroids;
}

void DrawAstroids(void)
{
    int i;
    for (i = 0; i < MAX_ASTROIDS; i++)
    {
        AstroidDraw(_astroids[i]);
    }
}

Astroid* AstroidsArray(void)
{
    return _astroids;
}

void DestroyAstroidAt(int index)
{
    Astroid* astroid = _astroids + index;
    int points = 0;
    astroid->active = false;

    switch (astroid->size)
    {
    case ASTROID_LARGE:
        // 2 medium
        AddAstroid(astroid->position, ASTROID_MEDIUM, 0.5f, false);
        AddAstroid(astroid->position, ASTROID_MEDIUM, 0.5f, false);
        break;
    case ASTROID_MEDIUM:
        // 2 small
        AddAstroid(astroid->position, ASTROID_SMALL, 0.33f, false);
        AddAstroid(astroid->position, ASTROID_SMALL, 0.33f, false);
        break;
    
    default:
        // no astroids
        break;
    }
    points = (int) astroid->size * 10;
    if (points <= 0)
    {
        TraceLog(LOG_INFO, "Tried to add negative or 0 to score");
        return;
    }
    AddScore(points);
}

void ResetAstroids(void)
{
    for (int i = 0; i < MAX_ASTROIDS; i++)
	{
		_astroids[i] = (Astroid){0};
	}
	
	_lastAstroidCreationTime = -1.0f;
}