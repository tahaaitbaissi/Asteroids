#include "game_score.h"
#include "constants.h"
#include <raylib.h>


static int _score = 0;

void ResetScore(void)
{
    _score = 0;
}

void AddScore(int points)
{
    _score += points;
}

void DrawScore(void)
{
    const Color black = Fade(BLACK, 0.8f);
    const Color white = Fade(WHITE, 0.8f);

    const int xPad = 16;
    const int yPad = 8;
    const int shadow = 8;

    char* textScore = TextFormat("%d", _score);
    char* textPts = "PTS";
    float measureScore = MeasureText(textScore, FONT_SIZE);
    float measurePts = MeasureText(textPts, 24);

    int x = SCREEN_WIDTH - measureScore - measurePts - xPad;
    int y = yPad;
    int xPts = x + measureScore + (xPad * 0.5f);
    int yPts = y + 24;

    DrawText(textScore, x + shadow, y + shadow, FONT_SIZE, black);
    DrawText(textPts, xPts + shadow, yPts + shadow, 24, black);
    DrawText(textScore, x, y, FONT_SIZE, white);
    DrawText(textPts, xPts, yPts, 24, white);
}