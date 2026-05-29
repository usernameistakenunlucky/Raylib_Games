#include "Ai.h"

Node* Ai::GetRandomNode()
{
	int randRow = GetRandomValue(0, ROWS - 1);
	int randColumn = GetRandomValue(0, COLUMNS - 1);

	while (grid[randRow][randColumn].blocked)
	{
		randRow = GetRandomValue(0, ROWS - 1);
		randColumn = GetRandomValue(0, COLUMNS - 1);
	}

	return &grid[randRow][randColumn];
}