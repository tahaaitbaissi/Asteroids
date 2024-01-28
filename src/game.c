#include "game.h"

#include "game_astroids.h"
#include "game_projectiles.h"
#include "game_score.h"
#include "game_player.h" 
#include "game_ui.h"
#include "debug.h"

#include "raygui.h"

static int _activeAstroids = 0;
static int _activeProjectiles = 0;

static GameState _state;

extern bool _quitGame;

static void SetState(GameState state)
{
    switch (state)
    {
    case GAME_MAIN_MENU:
        break;
    case GAME_PLAYING:
        ResetAstroids();
		ResetPlayer();
		ResetProjectiles();
		ResetScore();
        break;
    case GAME_OVER:
        break;
    default:
        break;
    }
    _state = state;    
}

void InitGame(void)
{
    InitPLayer();
}

void UpdateGame(void)
{
    _activeAstroids = UpdateAstroids();
    _activeProjectiles = UpdateProjetiles();
    UpdatePlayer();
}

void DrawGame(void)
{
    const int buttonWidth = 200;
	const int buttonHeight = 80;
	const Rectangle topButton = {SCREEN_CENTER.x - buttonWidth / 2, SCREEN_CENTER.y - buttonHeight / 2 - 5, buttonWidth, buttonHeight};
	const Rectangle bottomButton = {SCREEN_CENTER.x - buttonWidth / 2, SCREEN_CENTER.y + buttonHeight / 2 + 5, buttonWidth, buttonHeight};

    switch (_state)
    {
    case GAME_MAIN_MENU:
    if (GuiButton(topButton, "ASTEROIDS!"))
		{
			SetState(GAME_PLAYING);
			return;
		}

		if (GuiButton(bottomButton, "QUIT"))
		{
			_quitGame = true;
			return;
		}
        break;
    case GAME_PLAYING:
        DrawHealth();
        DrawAstroids();
        DrawProjectiles();
        DrawPlayer();
        DrawScore();
        ShowDebugVisualizations(_activeAstroids);
        ShowDebugMenu();
        break;

    case GAME_OVER:
        DrawAstroids();

        DrawRectangleRec(SCREEN_AREA, Fade(BLACK, 0.4f));
        const int fontSize = 64;
        const char* gameover = "GAME OVER!";
        float measure = MeasureText(gameover, fontSize);
        DrawText(gameover, SCREEN_CENTER.x - measure / 2, fontSize * 1.5f, fontSize, WHITE);
        DrawScore();

        if (GuiButton(topButton, "PLAY AGAIN?"))
        {
            SetState(GAME_PLAYING);
            return;
        }
        if (GuiButton(bottomButton, "QUIT"))
        {
            _quitGame = true;
            return;
        }


        break;

    default:
        TraceLog(LOG_ERROR, "Unhandled GameState!");
        break;
    }    


    
}

void GameOver(void)
{
    SetState(GAME_OVER);
}