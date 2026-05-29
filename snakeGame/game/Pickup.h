#pragma once
#include <raylib.h>
#include <vector>
#include <algorithm>
#include "Definitions.h"
#include "Piece.h"
#include "Player.h"

class Pickup
{
public:

	Vector2 position;
	Vector2 size = Vector2{ TILE_SIZE, TILE_SIZE };
	Color color = ORANGE;
	bool active = false;

	void NewRandomLocation(Vector2 borderGap, const Player& player)
	{
		int x = GetRandomValue(0, SCREEN_WIDTH / TILE_SIZE - 1) * TILE_SIZE + borderGap.x / 2;
		int y = GetRandomValue(0, SCREEN_HEIGHT / TILE_SIZE - 1) * TILE_SIZE + borderGap.y / 2;

		for (int i = 0; i < player.tail.size(); i++)
		{
			if (x == player.tail[i].position.x && y == player.tail[i].position.y)
			{
				x = GetRandomValue(0, SCREEN_WIDTH / TILE_SIZE - 1) * TILE_SIZE + borderGap.x / 2;
				y = GetRandomValue(0, SCREEN_HEIGHT / TILE_SIZE - 1) * TILE_SIZE + borderGap.y / 2;
				i = -1;
			}
		}
		position = Vector2{ (float)x, (float)y };
	}


	void Render()
	{
		Vector2 centerPos = Vector2{ position.x + TILE_SIZE / 2, position.y + TILE_SIZE / 2 };
		DrawCircleV(centerPos, TILE_SIZE / 2, color);
		DrawCircleV(centerPos, TILE_SIZE / 2.4, Color{
			(unsigned char)std::max(0, color.r - 30),
			(unsigned char)std::max(0, color.g - 30),
			(unsigned char)std::max(0, color.b - 30), 255});
		//draw stem
		DrawLineEx(Vector2{ centerPos.x, position.y }, Vector2{ centerPos.x, position.y + TILE_SIZE / 4 }, 12.f, BROWN);
	}

};