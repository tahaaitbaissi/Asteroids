#ifndef GAME_H_
#define GAME_H_

typedef enum
{
    GAME_MAIN_MENU,
    GAME_PLAYING,
    GAME_OVER
} GameState;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void GameOver(void);

#endif