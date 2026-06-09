#include "Ai.h"

void Ai::Restart()
{
	_state = AiState::waiting;

	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Reset();
		}
	}

	//block some of the nodes
	for (int i = 0; i < ROWS * COLUMNS * PERCENT_BLOCKED; i++)
	{
		Node* temp = GetRandomNode();
		temp->blocked = true;
		temp->fillColor = BLACK;
	}

	//random search variables
	currentPath.clear();
	currentVisited.clear();
	searchComplete = false;

	// bfs
	bfsTracedPath.clear(); // clear old path so it doesn't persist after restart
	drawBFSindex = 0;

	// dfs
	dfsTracedPath.clear(); // same ^
	drawDFSindex = 0;

	// djikstra
	djikstraOpenSet = std::priority_queue<Node*, std::vector<Node*>, Compare>();
	djikstraEndTrace = nullptr;
	drawDjikstraIndex = 0;
	djikstraTracedPath.clear();

	// djikstra
	aStarOpenSet = std::priority_queue<Node*, std::vector<Node*>, CompareAStar>();
	aStarEndTrace = nullptr;
	drawAStarIndex = 0;
	aStarTracedPath.clear();


	//set points A and B
	startPoint = GetRandomNode();
	startPoint->fillColor = GREEN;
	startPoint->blocked = true;
	startPoint->displayText = "S";

	endPoint = GetRandomNode();
	endPoint->fillColor = BLUE;
	endPoint->blocked = true;
	endPoint->displayText = "E";
}