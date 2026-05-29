#pragma once
#include <raylib.h>

enum class CardState
{
	hidden = 0,
	flipped,
	matched,
};

enum class GameState
{
	play = 0,
	win,
	hint,
};

constexpr int GRID_SIZE = 8; // mustbe even number
constexpr int WINDOW_HEIGHT = (400 * 1.1);
constexpr int WINDOW_WIDTH = 400;
constexpr int GAP = WINDOW_WIDTH * 0.02 / (GRID_SIZE * 0.5);

constexpr int UI_SIZE = WINDOW_WIDTH * 0.07;

constexpr int QM_WIDTH = UI_SIZE * 0.5; // using the logic inside raylib's "MeasureText"

constexpr float HINT_TIMER = 5.f;
constexpr int HINT_FONT = WINDOW_HEIGHT / 2;

constexpr int UI_FONT = (float)UI_SIZE * ((float)4 / (float)GRID_SIZE);
constexpr int TIMER_DURATION = 2;