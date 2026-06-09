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

void Ai::Interaction()
{
	if (IsKeyPressed(KEY_X)) { Restart(); }
	if (_state != AiState::waiting) { return; }

	if (IsKeyPressed(KEY_R)) { RandomSearch(startPoint, endPoint); }
	if (IsKeyPressed(KEY_B)) { BFS(startPoint, endPoint); }
	if (IsKeyPressed(KEY_D)) { DFS(startPoint, endPoint); }
	if (IsKeyPressed(KEY_J)) { Djikstra(startPoint, endPoint); }
	if (IsKeyPressed(KEY_A)) { AStar(startPoint, endPoint); }
}

void Ai::UpdateAll()
{
	DELTA_TIME = GetFrameTime();
	Interaction();

	switch (_state)
	{
	case AiState::BFS: { BFS(startPoint, endPoint); break; }
	case AiState::DFS: { DFS(startPoint, endPoint); break; }
	case AiState::djikstra: { Djikstra(startPoint, endPoint); break; }
	case AiState::aStar: { AStar(startPoint, endPoint); break; }
	}

	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Update();
		}
	}
}

void Ai::RenderAll()
{
	// Render nodes normally
	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Render();
		}
	}

	// BFS trace
	if (_state == AiState::traceBFS && drawBFSindex < bfsTracedPath.size()) 
	{ 
		bfsTracedPath[drawBFSindex]->StartAnim();  
		drawBFSindex++; 
		if (drawBFSindex == bfsTracedPath.size()) { _state = AiState::waiting; }
	}

	for (int i = 0; i < drawBFSindex; i++)
	{
		if (bfsTracedPath[i] == startPoint || bfsTracedPath[i] == endPoint) { continue; }
		bfsTracedPath[i]->DrawPath(PATH_COLOR);
	}

	// DFS trace
	if (_state == AiState::traceDFS && drawDFSindex < dfsTracedPath.size())
	{
		dfsTracedPath[drawDFSindex]->StartAnim();
		drawDFSindex++;
		if (drawDFSindex == dfsTracedPath.size()) { _state = AiState::waiting; }
	}

	for (int i = 0; i < drawDFSindex; i++)
	{
		if (dfsTracedPath[i] == startPoint || dfsTracedPath[i] == endPoint) { continue; }
		dfsTracedPath[i]->DrawPath(PATH_COLOR);
	}

	// Djikstra trace
	if (_state == AiState::traceDjikstra && drawDjikstraIndex < djikstraTracedPath.size())
	{
		djikstraTracedPath[drawDjikstraIndex]->StartAnim();
		drawDjikstraIndex++;
		if (drawDjikstraIndex == djikstraTracedPath.size()) { _state = AiState::waiting; }
	}

	for (int i = 0; i < drawDjikstraIndex; i++)
	{
		if (djikstraTracedPath[i] == startPoint || djikstraTracedPath[i] == endPoint) { continue; }
		djikstraTracedPath[i]->DrawPath(PATH_COLOR);
	}

	// AStar trace
	if (_state == AiState::traceAStar && drawAStarIndex < aStarTracedPath.size())
	{
		aStarTracedPath[drawAStarIndex]->StartAnim();
		drawAStarIndex++;
		if (drawAStarIndex == aStarTracedPath.size()) { _state = AiState::waiting; }
	}
	for (int i = 0; i < drawAStarIndex; i++)
	{
		if (aStarTracedPath[i] == startPoint || aStarTracedPath[i] == endPoint) { continue; }
		aStarTracedPath[i]->DrawPath(PATH_COLOR);
	}
}
