#include "Ai.h"

void Ai::Restart()
{
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

	//set points A and B
	start = GetRandomNode();
	start->fillColor = GREEN;
	start->blocked = true;
	start->displayText = "S";

	end = GetRandomNode();
	end->fillColor = BLUE;
	end->blocked = true;
	end->displayText = "E";
}