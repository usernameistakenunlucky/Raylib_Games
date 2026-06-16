#pragma once
#include <raylib.h>
#include <raymath.h>
#include <float.h>
#include "Definitions.h"

class Tile
{
public:

	int gridX;
	int gridY;   

	Vector2 position;
	Vector2 size;

	bool blocked = false;

	bool visited = false;
	Tile* parent = nullptr;
	int step = 0;

	float hCost = 0.f;
	float gCost = FLT_MAX;
	float fCost = FLT_MAX;

	Tile(int y, int x, bool b)
		:
		gridX(x),
		gridY(y),
		blocked(b)
	{
		float posX = gridX * TILE_SIZE;
		float posY = TILE_SIZE * gridY;
		position = Vector2{ posX,posY };

		size = Vector2{ TILE_SIZE, TILE_SIZE };
	}

	//void Update() {}

	void Render()
	{
		if (blocked)
		{
			DrawRectangleV(position + BORDER_GAP / 2, size, BLACK);
			DrawRectangleV(position + (BORDER_GAP / 2) + (size * 0.3 / 2), size * 0.7, DARKGRAY);
		}
		else
		{
			DrawRectangleV(position + BORDER_GAP / 2, size, TILE_COLOR);
		}

		DrawRectangleLinesV(position + BORDER_GAP / 2, size, 5.f, DARKGRAY);
	}

	void Reset(bool visitation = false)
	{
		if (!visitation) // this is reset ONLY, not used for searches
		{
			blocked = false;
			gCost = FLT_MAX;
			hCost = 0.f;
			fCost = FLT_MAX;
		}

		visited = false;
		parent = nullptr;
		step = 0;
	}

};