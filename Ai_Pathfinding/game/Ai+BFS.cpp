#include <queue>
#include <iostream>
#include "Ai.h"

void Ai::BFS(Node* start, Node* end)
{
	// tell us if you found a path OR not
	// and if you found one, populate the bfsTracedPath

	if (_state == AiState::waiting)
	{
		bfsTracedPath.clear();
		bfsFoundEnd = false;
		bfsEndTrace = nullptr;
		drawBFSindex = 0;

		for (auto& row : grid)
		{
			for (auto& node : row)
			{
				node.Reset(true);
			}
		}

		// this is that array i was drawing
		// FIFO -> process items in the order they arrive
		while (!bfsOpenSet.empty()) { bfsOpenSet.pop(); }
		bfsOpenSet.push(start);
		start->visited = true;

		_state = AiState::BFS;
		return;
	}

	if (bfsFoundEnd)
	{
		if (bfsEndTrace != nullptr && bfsEndTrace != start)
		{
			bfsTracedPath.emplace_back(bfsEndTrace);
			bfsEndTrace = bfsEndTrace->parent;
		}
		else
		{
			std::reverse(bfsTracedPath.begin(), bfsTracedPath.end());
			drawBFSindex = 0;
			_state = AiState::traceBFS;
		}
		return;
	}

	if (!bfsOpenSet.empty())
	{
		Node* current = bfsOpenSet.front();
		bfsOpenSet.pop();

		if (current != start && current != end)
		{
			current->fillColor = BFS_COLOR;
			current->StartAnim();
		}

		if (current == end)
		{
			bfsFoundEnd = true;
			bfsEndTrace = end;
			std::cout << "BFS path was found\n";
			return;
		}

		for (Node* neighbor : GetNeighbors(current))
		{
			if ((neighbor->blocked || neighbor->visited) && neighbor != end) { continue; }

			neighbor->parent = current;
			neighbor->step = current->step + 1;
			neighbor->visited = true;
			bfsOpenSet.push(neighbor);
		}
	}
	else
	{
		std::cout << "BFS path NOT found!\n";
		_state = AiState::waiting;
	}
}