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

	int value = 0;

	Vector2 position;
	Vector2 size = Vector2{ TILE_SIZE, TILE_SIZE };
	Color color = WHITE;
	bool active = true;

	Pickup(const Vector2& freePostion)
		: position(freePostion)
	{
	}

	virtual ~Pickup() = default;

	virtual void Update() {}
	virtual void Render() {}
	virtual void Effect(Player& player) {}
	virtual Color GetColor() const { return WHITE; }
};