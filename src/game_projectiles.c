#include "game_projectiles.h"
#include "constants.h"
#include "game_astroids.h"

#define PROJECTILE_MAX 12

static Projectile _projectiles[PROJECTILE_MAX];

void AddProjectile(Vector2 position, float rotation)
{
    bool created = false;
    int i;

    for (i = 0; i < PROJECTILE_MAX; i++)
    {
        if (_projectiles[i].active)
            continue;

        _projectiles[i] = CreateProjectile(position, rotation);
        created = true;
        break;
    }

    if (!created)
    {
        TraceLog(LOG_ERROR, "Failed to create a projectile becaus there was no inactive spots in the array.");
    }
}

static bool CheckCollisionProjectile(Projectile* projectile, Astroid* astroid)
{
    return (!astroid->active)
        ? false
        : CheckCollisionPointCircle(projectile->position, astroid->position, AstroidRadius(*astroid));
}

int UpdateProjetiles(void)
{
    int i, j, projectileCount = 0;
    float frameTime = GetFrameTime();
    float time = GetTime();

    Astroid* astroids = AstroidsArray();

    for (i = 0; i < PROJECTILE_MAX; i++)
    {
        Projectile* projectile = _projectiles + i;
        if (ProjectileUpdate(projectile, frameTime, time))
        {
            projectileCount++;
            bool hit = false;
            for (j = 0; j < MAX_ASTROIDS; j++)
            {
                Astroid* astroid = astroids + j;
                if (CheckCollisionProjectile(projectile, astroid))
                {
                    // points earned?
                    // create 2 new astroids
                    hit = true;
                    DestroyAstroidAt(j);
                    projectile->active = false;
                } 
            }
        }
    }

    return projectileCount;
}

void DrawProjectiles(void)
{
    int i;

    for (i = 0; i < PROJECTILE_MAX; i++)
    {
        ProjectileDraw(_projectiles[i]);
    }
}

void ResetProjectiles(void)
{
    for (int i = 0; i < PROJECTILE_MAX; i++)
	{
		_projectiles[i] = (Projectile){0};
	}
}