#ifndef DEBUG_H_
#define DEBUG_H_

#include <raylib.h>

void ShowDebugMenu(void);
void ShowDebugVisualizations(int astroidCount);
void SetLastCone(Vector2 position, Vector2 velocity);
void SetPlayerInfo(Vector2 position, Vector2 velocity, float rotation);


#endif