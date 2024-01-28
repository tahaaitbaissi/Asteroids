#include "projectile.h"

#include <math.h>

Projectile CreateProjectile(Vector2 position, float rotation)
{
    return (Projectile) {
        .position = position,
        .rotation = rotation,
        .active = true,
        .creationTime = GetTime()
    };
}

bool ProjectileUpdate(Projectile *projectile, float frameTime, float time)
{
    double radians = DEG2RAD * (projectile->rotation - 90.0f);
    if (!projectile->active)
    {
        return false;
    }
    
    if (time > projectile->creationTime + PROJECTILE_LIFE)
    {
        projectile->active = false;
        return false;
    }

    projectile->position.x += PROJECTILE_SPEED * frameTime * cos(radians);
    projectile->position.y += PROJECTILE_SPEED * frameTime * sin(radians);

    return true;
}

void ProjectileDraw(Projectile projectile)
{
    if (!projectile.active)
    {
        return;
    }

    Rectangle rect = {projectile.position.x, projectile.position.y, PROJECTILE_THICK
        ,PROJECTILE_LEN};
    Vector2 origin = {rect.width / 2, rect.height / 2};
    DrawRectanglePro(rect, origin, projectile.rotation, PROJECTILE_COLOR);
}