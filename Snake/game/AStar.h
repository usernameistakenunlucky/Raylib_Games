#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <queue>
#include <algorithm>
#include "Definitions.h"
#include "Piece.h"
#include "Tile.h"

struct AStar
{
	struct Heuristic
	{
		float operator()(Tile* a, Tile* b)
		{
			return (float)(abs(a->gridX - b->gridX) + abs(a->gridY - b->gridY));
		}
	};

	struct CompareAStar
	{
		bool operator()(Tile* a, Tile* b)
		{
			return a->fCost > b->fCost || (a->fCost == b->fCost && a->hCost > b->hCost);
		}
	};

	// Runs a full A* search from start to end on the given grid.
	// Returns the FIRST tile the player should step into, or nullptr if no path found.
	Tile* Search(std::vector<std::vector<Tile>>& grid, Tile* start, Tile* end)
	{
		// --- reset grid costs and visitation ---
		for (auto& row : grid)
		{
			for (auto& tile : row)
			{
				tile.visited = false;
				tile.parent = nullptr;
				tile.gCost = FLT_MAX;
				tile.hCost = 0.f;
				tile.fCost = FLT_MAX;
			}
		}

		std::priority_queue<Tile*, std::vector<Tile*>, CompareAStar> openSet;

		start->gCost = 0;
		Heuristic heuristic;
		start->hCost = heuristic(start, end);
		start->fCost = start->hCost;
		openSet.push(start);
		start->visited = true;

		while (!openSet.empty())
		{
			Tile* current = openSet.top();
			openSet.pop();

			if (current == end)
			{
				// trace back to find the first step after start
				Tile* step = end;
				while (step->parent != nullptr && step->parent != start)
				{
					step = step->parent;
				}
				// if end is directly adjacent to start, step == end, that's fine
				return step;
			}

			for (Tile* neighbor : GetNeighbors(grid, current))
			{
				if (neighbor->blocked && neighbor != end) { continue; }

				float tentativeCost = current->gCost + 1.f;
				if (tentativeCost < neighbor->gCost)
				{
					neighbor->gCost = tentativeCost;
					neighbor->hCost = heuristic(neighbor, end);
					neighbor->fCost = neighbor->gCost + neighbor->hCost;
					neighbor->parent = current;

					if (!neighbor->visited)
					{
						neighbor->visited = true;
						openSet.push(neighbor);
					}
				}
			}
		}

		return nullptr; // no path found
	}

	// Returns the 4 orthogonal neighbors of a tile
	std::vector<Tile*> GetNeighbors(std::vector<std::vector<Tile>>& grid, Tile* tile)
	{
		std::vector<Tile*> neighbors;
		int row = tile->gridY;
		int col = tile->gridX;

		if (row > 0) { neighbors.push_back(&grid[row - 1][col]); }
		if (row < (int)grid.size() - 1) { neighbors.push_back(&grid[row + 1][col]); }
		if (col > 0) { neighbors.push_back(&grid[row][col - 1]); }
		if (col < (int)grid[0].size() - 1) { neighbors.push_back(&grid[row][col + 1]); }

		return neighbors;
	}
};