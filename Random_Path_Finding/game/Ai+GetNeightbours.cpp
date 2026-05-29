#include "Ai.h"

std::vector<Node*> Ai::GetNeighbours(Node* node)
{
	std::vector<Node*> neighbours;
	int gridX = node->gridX;
	int gridY = node->gridY;

	auto isWithinGrid = [&](int x, int y) -> bool
		{
			return y >= 0 && x >= 0 && y < ROWS && x < COLUMNS;
		};

	auto addIfValid = [&](int x, int y)
		{
			if (isWithinGrid(x, y) && (!grid[y][x].blocked || &grid[y][x] == end))
			{
				neighbours.push_back(&grid[y][x]);
			}
		};

	addIfValid(gridX, gridY - 1);
	addIfValid(gridX, gridY + 1);
	addIfValid(gridX - 1, gridY);
	addIfValid(gridX + 1, gridY);

	return neighbours;
}