#include "Ai.h"
#include "raylib.h"
#include "Definitions.h"

void Ai::Main()
{
	Start();

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ai Pathfinding");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		Interaction();
		UpdateAll();

		BeginDrawing();
		ClearBackground(WHITE);

		
		RenderAll();

		EndDrawing();
	}

	CloseWindow();
}

void Ai::Start()
{
	//initialize grid
	for (int row = 0; row < ROWS; row++)
	{
		std::vector<Node> rowNodes;

		for (int col = 0; col < COLUMNS; col++)
		{
			Node newNode(row, col, false);
			rowNodes.push_back(newNode);
		}

		grid.push_back(rowNodes);
	}

	Restart();

}
