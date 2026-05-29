#pragma once
#include <raylib.h>
#include "Definitions.h"

class Piece
{
public:

	Vector2 position;
	Vector2 prevPosition;
	Vector2 size = Vector2{ TILE_SIZE, TILE_SIZE };
	Color color;
	char direction;

	Piece(const Vector2& positionInput, const Color& colorInput = GREEN)
		: position(positionInput), color(colorInput)
	{
	}

	void Update()
	{
		if (position.x > prevPosition.x) { direction = 'R'; }
		if (position.x < prevPosition.x) { direction = 'L'; }
		if (position.y > prevPosition.y) { direction = 'D'; }
		if (position.y < prevPosition.y) { direction = 'U'; }
	}

	void Render() 
	{ 
		DrawRectangleV(position, size, color); 
	}
};