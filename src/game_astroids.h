#ifndef ASTROIDS_H_
#define ASTROIDS_H_

#include "astroid.h"

void AddAstroid(Vector2 position, AstroidSize size, float speedMod, bool spawn);
Vector2 GetNextAstroidPosition(void);
int UpdateAstroids(void);
void DrawAstroids(void);
Astroid* AstroidsArray(void);
void DestroyAstroidAt(int index);
void ResetAstroids(void);

#endif