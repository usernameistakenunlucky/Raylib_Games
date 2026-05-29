#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "Definitions.h"
#include "Piece.h"

class Player
{
public:

	Vector2 direction; // move as much a tile to the right initially
	std::vector<Piece> tail;
	int tailCount = 1;
	bool canMove = false;

	void AddPiece()
	{
		tail.emplace_back(Piece(Vector2{ -1000, -1000 })); //spawn off screen, then snaps to end of tail
	}

	bool HitBorder()
	{
		if (tail[0].position.x >= RIGHT_BOUNDS ||
			tail[0].position.x < LEFT_BOUNDS ||
			tail[0].position.y >= BOTTOM_BOUNDS ||
			tail[0].position.y < TOP_BOUNDS)
		{
			return true;
		}
		return false;
	}

	bool HitSelf()
	{
		for (int i = 1; i < tail.size(); i++)
		{
			if (tail[i].position == tail[0].position) { return true; }
		}
		return false;
	}

	void Update(int frameCount)
	{
		if (frameCount % GAME_SPEED == 0)
		{
			for (int i = tail.size() - 1; i > 0; i--)
			{
				tail[i].prevPosition = tail[i].position;
				tail[i].position = tail[i - 1].position;
				tail[i].Update();
			}
			tail[0].prevPosition = tail[0].position;
			tail[0].position += direction;
			tail[0].Update();
			canMove = true;
		}
	}

	void Render()
	{
		for (int i = 0; i < tail.size(); i++)
		{
			tail[i].Render();
			if (i == 0)
			{
				// draw tongue on head
				switch (tail[i].direction)
				{
				case 'U': DrawLineEx(
					Vector2{ tail[i].position.x + TILE_SIZE / 2, tail[i].position.y },
					Vector2{ tail[i].position.x + TILE_SIZE / 2, tail[i].position.y - TILE_SIZE / 4 }, 12.f, RED); break;
				case 'D': DrawLineEx(
					Vector2{ tail[i].position.x + TILE_SIZE / 2, tail[i].position.y + TILE_SIZE },
					Vector2{ tail[i].position.x + TILE_SIZE / 2, tail[i].position.y + TILE_SIZE + TILE_SIZE / 4 }, 12.f, RED); break;
				case 'L': DrawLineEx(
					Vector2{ tail[i].position.x, tail[i].position.y + TILE_SIZE / 2 },
					Vector2{ tail[i].position.x - TILE_SIZE / 4, tail[i].position.y + TILE_SIZE / 2 }, 12.f, RED); break;
				case 'R': DrawLineEx(
					Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y + TILE_SIZE / 2 },
					Vector2{ tail[i].position.x + TILE_SIZE + TILE_SIZE / 4, tail[i].position.y + TILE_SIZE / 2 }, 12.f, RED); break;
				}
			}
			else
			{
				// draw triangles on body
				switch (tail[i].direction)
				{
				case 'U': DrawTriangle(
					Vector2{ tail[i].position.x + TILE_SIZE / 2, tail[i].position.y },
					Vector2{ tail[i].position.x, tail[i].position.y + TILE_SIZE },
					Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y + TILE_SIZE }, DARKGREEN); break;

				case 'D': DrawTriangle(
					Vector2{ tail[i].position.x + TILE_SIZE / 2, tail[i].position.y + TILE_SIZE },
					Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y },
					Vector2{ tail[i].position.x, tail[i].position.y }, DARKGREEN); break;

				case 'R': DrawTriangle(
					Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y + TILE_SIZE / 2 },
					Vector2{ tail[i].position.x, tail[i].position.y },
					Vector2{ tail[i].position.x, tail[i].position.y + TILE_SIZE }, DARKGREEN); break;

				case 'L': DrawTriangle(
					Vector2{ tail[i].position.x, tail[i].position.y + TILE_SIZE / 2 },
					Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y + TILE_SIZE },
					Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y }, DARKGREEN); break;
				}
			}
		}
	}
};