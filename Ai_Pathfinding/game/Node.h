#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Definitions.h"
#include <string>
#include <float.h>

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

	bool visited = false;
	Node* parent = nullptr;
	int step = 0;

	float hCost = 0.f;
	float gCost = FLT_MAX; //initialize each node's weight to infinity
	float fCost = FLT_MAX; 

	float animTimer = 0.f;

	NodeRenderState state = NodeRenderState::still;

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

	void Update()
	{
		switch (state)
		{
		case NodeRenderState::growing:
			animTimer -= DELTA_TIME * NODE_ANIM_SPEED;
			if (animTimer <= -1.f) { state = NodeRenderState::shrinking; }
			break;

		case NodeRenderState::shrinking:
			animTimer += DELTA_TIME * 6;
			if (animTimer >= 0.f)
			{
				animTimer = 0.f;
				fillColor = Color{
					(unsigned char)(fillColor.r * 0.8f),
					(unsigned char)(fillColor.g * 0.8f),
					(unsigned char)(fillColor.b * 0.9f),
					(unsigned char)(fillColor.a) };
				state = NodeRenderState::still;
			}
			break;

		default:;
		}
	}

	void StartAnim()
	{
		animTimer = NODE_ANIM_TIME;
		state = NodeRenderState::growing;
	}

	void DrawNodeAnimated(Color color)
	{
		float t = 1.0f - (animTimer / NODE_ANIM_TIME); // >1 when animTimer is negative
		Vector2 tempSize = { size.x * t, size.y * t };
		Vector2 tempPosition = Vector2{
			position.x + (size.x - tempSize.x) / 2,
			position.y + (size.y - tempSize.y) / 2 };

		DrawRectangleV(tempPosition, tempSize, color);
	}

	void Render()
	{
		if (blocked)
		{
			DrawRectangleV(position, size, fillColor);
		}
		else if (fillColor.r != WHITE.r || fillColor.g != WHITE.g || fillColor.b != WHITE.b)
		{
			if (state == NodeRenderState::still) { DrawRectangleV(position, size, fillColor); }
			else { DrawNodeAnimated(fillColor); }
		}

		DrawRectangleLinesV(position, size, outlineColor);

		if (step != 0 && displayText != "E") { displayText = std::to_string(step); }

		if (!displayText.empty())
		{
			int textHeight = 20;
			int textWidth = MeasureText(displayText.c_str(), textHeight);
			Vector2 textPosition = Vector2{ position.x + size.x / 2 - textWidth / 2,
										   position.y + size.y / 2 - textHeight / 2 };

			DrawText(displayText.c_str(), textPosition.x, textPosition.y, textHeight, BLACK);
		}
	}

	void DrawPath(Color color) // used only for tracedPath drawing
	{
		DrawRectangleV(position, size, fillColor);
		if (state != NodeRenderState::still) { DrawNodeAnimated(color); }
		else { DrawRectangleV(position, size, color); }

		if (!displayText.empty())
		{
			int textHeight = 20;
			int textWidth = MeasureText(displayText.c_str(), textHeight);
			Vector2 textPosition = Vector2{
				position.x + size.x / 2 - textWidth / 2,
				position.y + size.y / 2 - textHeight / 2 };

			DrawText(displayText.c_str(), textPosition.x, textPosition.y, textHeight, BLACK);
		}
	}

	void Reset(bool visitation = false)
	{
		if (!visitation) // this is reset ONLY, not used for searches
		{
			state = NodeRenderState::still;
			animTimer = 0.f;
			blocked = false;
			displayText = "";
			fillColor = WHITE;
			gCost = FLT_MAX;
			hCost = 0.f;
			fCost = FLT_MAX;
		}

		visited = false;
		parent = nullptr;
		step = 0;
	}

};