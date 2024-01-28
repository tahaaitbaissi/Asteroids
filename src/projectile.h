#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include <raylib.h>

#define PROJECTILE_SPEED 600
#define PROJECTILE_LIFE 2.0f
#define PROJECTILE_THICK 10.0f
#define PROJECTILE_LEN 30.0f
#define PROJECTILE_COLOR CLITERAL (Color) {245, 201, 207, 255}

typedef struct 
{
    Vector2 position;
    float rotation;
    bool active;
    float creationTime;
} Projectile;

Projectile CreateProjectile(Vector2 position, float rotation);
bool ProjectileUpdate(Projectile* projectile, float frameTime, float time);
void ProjectileDraw(Projectile projectile);

#endif