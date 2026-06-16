#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <queue>
#include "Definitions.h"
#include "Piece.h"
#include "Tile.h"
#include "AStar.h"

class Player
{
public:

	int score = 0;

	Vector2 direction;
	std::vector<Piece> tail;
	int tailCount = 1;
	float magicTimer = 0.f;
	bool canMove = false;

	AStar aStar;


	Player() {}

	void AddPiece() { tail.emplace_back(Piece(Vector2{ -1000, -1000 })); } // spawns off screen, snaps to end of tail

	bool IsMagicControlled() const { return magicTimer > 0.f; }
	void SetMagic(float time) { magicTimer = time; }
	bool HitBorder();
	bool HitSelf();
	bool HitWall(std::vector<std::vector<Tile>>& grid);

	void Reset();

	// grid and pickupTile are needed for A* during magic mode
	void Update(int frameCount, std::vector<std::vector<Tile>>& grid, Tile* pickupTile);
	void Render(const Color& magicColor);
};