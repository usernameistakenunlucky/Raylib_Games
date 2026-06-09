#include <iostream>
#include "Ai.h"

void Ai::Djikstra(Node* start, Node* end)
{
	if (_state == AiState::waiting)
	{
		djikstraTracedPath.clear();
		djikstraFoundEnd = false;
		djikstraEndTrace = nullptr;
		drawDjikstraIndex = 0;

		for (auto& row : grid)
		{
			for (auto& node : row)
			{
				node.Reset(true);
			}
		}

		while (!djikstraOpenSet.empty()) { djikstraOpenSet.pop(); }
		start->gCost = 0;
		djikstraOpenSet.push(start);
		start->visited = true;

		_state = AiState::djikstra;
		return;
	}

    if (djikstraFoundEnd)
    {
        if (djikstraEndTrace != nullptr && djikstraEndTrace != start)
        {
            djikstraTracedPath.emplace_back(djikstraEndTrace);
            djikstraEndTrace = djikstraEndTrace->parent;
        }
        else
        {
            std::reverse(djikstraTracedPath.begin(), djikstraTracedPath.end());
            drawDjikstraIndex = 0;
            _state = AiState::traceDjikstra;
        }
        return;
    }

    if (!djikstraOpenSet.empty())
    {
        Node* current = djikstraOpenSet.top();
        djikstraOpenSet.pop();

        if (current != start && current != end)
        {
            current->fillColor = DJIKSTRA_COLOR;
            current->StartAnim();
        }

        if (current == end)
        {
            djikstraFoundEnd = true;
            djikstraEndTrace = end;
            std::cout << "Djikstra path found!\n";
            return;
        }

        for (auto neighbor : GetNeighbors(current))
        {
            if (neighbor->blocked && neighbor != end) { continue; }

            float tentativeCost = current->gCost + 1;
            if (tentativeCost < neighbor->gCost)
            {
                neighbor->gCost = tentativeCost;
                neighbor->parent = current;
                neighbor->step = current->step + 1;
                djikstraOpenSet.push(neighbor);
            }
        }
    }
    else
    {
        std::cout << "No Djikstra path!\n";
        _state = AiState::waiting;
    }

}