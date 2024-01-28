#ifndef PLAYER_H_
#define PLAYER_H_

#include <raylib.h>
#include "constants.h"

#define PLAYER_ROT_SPEED 360
#define PLAYER_SPEED 250
#define PLAYER_ACCELERATION 750
#define PLAYER_DECELERATION 175
#define PLAYER_RADIUS 24
#define PLAYER_NUDGE_VELOCITY 100
#define PLAYER_PROJECTILE_OFFSET PLAYER_RADIUS
#define PLAYER_FIRE_DELAY 0.33f
#define PLAYER_COLLISION_NUDGE 150.0f
#define PLAYER_STUN_DURATION 0.2f
#define PLAYER_IFRAME_DURATION 0.8f
#define PLAYER_HEALTH_MAX 5
#define PLAYER_DEATH_DELAY 1.5f

#define FIELD_MIN_X (- PLAYER_RADIUS / 2)
#define FIELD_MAX_X (SCREEN_WIDTH + PLAYER_RADIUS / 2)
#define FIELD_MIN_Y (- PLAYER_RADIUS / 2)
#define FIELD_MAX_Y (SCREEN_HEIGHT + PLAYER_RADIUS / 2)

typedef enum
{
    PLAYER_DEFAULT,
    PLAYER_STUNNED,
    PLAYER_IFRAME,
    PLAYER_DEAD
} PlayerState;

typedef struct 
{
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float lastFireTime;
    PlayerState state;
    float timeStateEntered;
} Player;

void PlayerMove(Player* player);
void PlayerDraw(Player player, Texture2D texture);
Vector2 PlayerFacingDirection(Player player);
void PlayerSetState(Player* player ,PlayerState state);

#endif