#include "game_player.h"
#include "constants.h"
#include "game_projectiles.h"
#include "game_astroids.h"
#include "game.h"
#include <raymath.h>

static Player _player;
static Texture2D _texturePlayer;
static int _health = PLAYER_HEALTH_MAX;

void InitPLayer(void)
{
    ResetPlayer();
    _texturePlayer = LoadTexture("resources/ship.png");
}

void ResetPlayer(void)
{
    _player = (Player) {
        .position = SCREEN_CENTER,
        .rotation = 0,
        .velocity = (Vector2) {0},
        .lastFireTime = -1.0f,
        .state = PLAYER_DEFAULT
    };
    _health = PLAYER_HEALTH_MAX;
}

static void Ondeath(void)
{
    PlayerSetState(&_player, PLAYER_DEAD);
}

static void OnCollision(Astroid* astroid)
{
    const float astroidSpeedReduction = 0.4f;

    _health--;
    if (_health <= 0)
    {
        Ondeath();
        return;
    }

    Vector2 nudgeDirection = Vector2Normalize(Vector2Subtract(_player.position, astroid->position));
    _player.velocity = Vector2Scale(nudgeDirection, PLAYER_COLLISION_NUDGE);
    astroid->velocity = Vector2Scale(astroid->velocity, astroidSpeedReduction);

    PlayerSetState(&_player, PLAYER_STUNNED);

}

static void TickState(void)
{
    switch (_player.state)
    {
    case PLAYER_DEFAULT:
        break;
    case PLAYER_STUNNED:
        if ((GetTime() - _player.timeStateEntered) > PLAYER_STUN_DURATION)
        {
            PlayerSetState(&_player, PLAYER_IFRAME);
        }
        break;
    case PLAYER_IFRAME:
        if ((GetTime() - _player.timeStateEntered) > PLAYER_IFRAME_DURATION)
        {
            PlayerSetState(&_player, PLAYER_DEFAULT);
        }
        break;
    case PLAYER_DEAD:
        if ((GetTime() - _player.timeStateEntered) > PLAYER_DEATH_DELAY)
        {
            GameOver();
        }
        break;
    default:
        TraceLog(LOG_ERROR, "PlayerState %d not handled.", (int)_player.state);
        break;
    }
}

void UpdatePlayer(void)
{
    PlayerMove(&_player);
    TickState();
    if (_player.state == PLAYER_STUNNED)
    {
        return;
    }
    float time = GetTime();
    Astroid* astroids = AstroidsArray();
    Vector2 facingDirection = PlayerFacingDirection(_player);

    if (IsKeyDown(KEY_SPACE))
    {
        if (time > _player.lastFireTime + PLAYER_FIRE_DELAY)
        {
            AddProjectile(Vector2Add(_player.position, 
                Vector2Scale(facingDirection, PLAYER_PROJECTILE_OFFSET)), _player.rotation);
            
            _player.lastFireTime = time;
        }
    }

    if (_player.state == PLAYER_IFRAME)
    {
        return;
    }

    for (int i = 0; i < MAX_ASTROIDS; i++)
    {
        Astroid* astroid = astroids + i;
        if (!astroid->active)
        {
            continue;
        }

        if (!CheckCollisionCircles(_player.position, PLAYER_RADIUS,
                astroid->position, AstroidRadius(*astroid)))
        {
            continue;
        }

        OnCollision(astroid);
    }
}

void DrawPlayer(void)
{
    PlayerDraw(_player, _texturePlayer);
}

int PlayerHealth(void)
{
    return _health;
}