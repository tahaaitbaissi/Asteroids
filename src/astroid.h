#ifndef ASTROID_H_
#define ASTROID_H_

#include <raylib.h>

#define ASTROID_ROT_SPEED_MIN 5
#define ASTROID_ROT_SPEED_MAX 240
#define ASTROID_SPEED_MIN 100
#define ASTROID_SPEED_MAX 300

#define ASTROID_LIFE 10.0f

typedef enum
{
    ASTROID_SMALL = 1,
    ASTROID_MEDIUM = 2,
    ASTROID_LARGE = 4
} AstroidSize;

typedef struct
{
    bool active;
    AstroidSize size;
    Vector2 position;
    float rotation;
    float rotationSpeed;
    Vector2 velocity;
    float creationTime;
} Astroid;

Astroid CreateAstroid(Vector2 position, Vector2 velocity, AstroidSize size);
bool AstroidUpdate(Astroid* astroid, float frametime, float time);
void AstroidDraw(Astroid astroid);
float AstroidRadius(Astroid astroid);

#endif