#ifndef GAME_PROJECTILES_H_
#define GAME_PROJECTILES_H_

#include "projectile.h"

void AddProjectile(Vector2 position, float rotation);
int UpdateProjetiles(void);
void DrawProjectiles(void);
void ResetProjectiles(void);

#endif