#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "Button.h"
#include "Definitions.h"

struct TrailSegment
{
	Color color;
	Vector2 pos;
	float thickness;
};

class SpiroGraph
{
private:
	float canvasRadius = WINDOW_HEIGHT / 2;

	float time = 0.0f;
	Vector2 canvasCenter = { WINDOW_HEIGHT / 2 + UI_OFFSET, WINDOW_HEIGHT / 2 };

	//wheel
	float wheelR = 222.f;
	Vector2 wheelPos = { canvasCenter.x + canvasRadius - wheelR, canvasCenter.y };
	float speed = 3.f;

	//pen
	float penOffset = 100.f;
	float currentThickness = 2.f;
	Vector2 penPos = { wheelPos.x + penOffset, canvasCenter.y };
	Color currentColor = PURPLE;

	std::vector<TrailSegment> trail;
	std::vector<Button> colors;

public:
	SpiroGraph()
	{
	}

	void Start();
	void Main();
	void UserInput();
	void UpdateAll();
	void RenderAll();
};
