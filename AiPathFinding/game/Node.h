#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Definitions.h"
#include <string>

struct Node
{
	int gridX; // 
	int gridY; //    


	Vector2 position;
	Vector2 size; // 25, 25
	Color fillColor;
	Color outlineColor;
	std::string displayText;

	bool blocked = false;

	Node(int r, int c, bool b, Color fc = WHITE, Color oc = BLACK)
		:
		gridY(r),
		gridX(c),
		blocked(b),
		fillColor(fc),
		outlineColor(oc)
	{
		float posX = gridX * NODE_SIZE;
		float posY = NODE_SIZE * gridY;
		position = Vector2{ posX,posY };

		size = Vector2{ NODE_SIZE, NODE_SIZE };
	}

	void Draw()
	{
		if (blocked)
		{
			DrawRectangleV(position, size, fillColor);
		}
		else if (fillColor.r != WHITE.r || fillColor.g != WHITE.g || fillColor.b != WHITE.b)
		{
			DrawRectangleV(position, size, fillColor);
		}

		DrawRectangleLinesV(position, size, outlineColor); 

		if (!displayText.empty())
		{
			int textHeight = 20;
			int textWidth = MeasureText(displayText.c_str(), textHeight);
			Vector2 textPosition = Vector2{ position.x + size.x / 2 - textWidth / 2,
										   position.y + size.y / 2 - textHeight / 2 };

			DrawText(displayText.c_str(), textPosition.x, textPosition.y, textHeight, BLACK);
		}
	}

	void Reset()
	{
		blocked = false;
		displayText = "";
		fillColor = WHITE;
	}

};