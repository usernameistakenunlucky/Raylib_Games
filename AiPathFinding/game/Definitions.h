#pragma once

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

#define PERCENT_BLOCKED 0.25
#define COLUMNS 20
#define ROWS 20
#define NODE_SIZE 50 // w/h of each tile
#define DARKEN_RATE 30 // speed at which it darkens failed paths


inline void DrawRectangleLinesV(Vector2 position, Vector2 size, Color color)
{
	DrawRectangleLines(position.x, position.y, size.x, size.y, color);
}