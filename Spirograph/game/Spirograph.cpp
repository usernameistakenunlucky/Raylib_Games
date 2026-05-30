#include "Spirograph.h"

void SpiroGraph::Start()
{
	colors.push_back({ 50, 50, 100, 100, RED });
	colors.push_back({ 200, 50, 100, 100, GREEN });
	colors.push_back({ 350, 50, 100, 100, PURPLE });

	colors.push_back({ 50, 200, 100, 100, YELLOW });
	colors.push_back({ 200, 200, 100, 100, BLUE });
	colors.push_back({ 350, 200, 100, 100, ORANGE });
}

void SpiroGraph::Main()
{
	Start();

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SpiroGraph");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		DrawCircleV(canvasCenter, canvasRadius, WHITE); //white circle bg

		UserInput();
		UpdateAll();

		wheelPos.x = (canvasRadius + cosf(time) * (canvasRadius - wheelR)) + UI_OFFSET;
		wheelPos.y = canvasRadius + sinf(time) * (canvasRadius - wheelR);

		penPos.x = canvasCenter.x + (canvasRadius - wheelR) * cosf(time) + penOffset * cosf((canvasRadius - wheelR) / wheelR * time);
		penPos.y = canvasCenter.y + (canvasRadius - wheelR) * sinf(time) - penOffset * sinf((canvasRadius - wheelR) / wheelR * time);
		trail.push_back(TrailSegment{ currentColor , penPos, currentThickness });

		RenderAll();

		EndDrawing();
	}

	CloseWindow();
}

void SpiroGraph::UserInput()
{
	float mouseToCanvasEdge = Vector2Distance(GetMousePosition(), canvasCenter);
	if (mouseToCanvasEdge >= canvasRadius - 20)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			canvasRadius = mouseToCanvasEdge;
			if (canvasRadius > WINDOW_HEIGHT / 2) { canvasRadius = WINDOW_HEIGHT / 2; };
		}
	}

	if (IsKeyDown(KEY_LEFT))
	{
		penOffset -= 1;
		if (penOffset < 0) { penOffset = 0.f; }

	}
	if (IsKeyDown(KEY_RIGHT))
	{
		penOffset += 1;
		if (penOffset > wheelR) { penOffset = wheelR; }
	}
	if (IsKeyPressed(KEY_SPACE))
	{
		trail.clear();
		time = 0.0f;

	}
}

void SpiroGraph::UpdateAll()
{
	time += GetFrameTime() * speed;

	for (auto& button : colors)
	{
		if (button.IsMouseClickingBox())
		{
			button.SetSelected(true);
			currentColor = button.GetColor();
		}
		button.Update(currentColor);
	}
}

void SpiroGraph::RenderAll()
{
	// drawing wheel

	DrawCircleLinesV(wheelPos, wheelR, RED);
	DrawCircleV(wheelPos, 10.f, RED);

	DrawLineV(wheelPos, penPos, BLACK);
	DrawCircleV(penPos, 10.f, BLACK);

	for (int i = 0; i < trail.size() - 1; i++) { DrawLineEx(trail[i].pos, trail[i + 1].pos, trail[i + 1].thickness, trail[i + 1].color); }

	// Drawing buttons
	for (const auto& button : colors)
	{
		button.Render();
	}
}
