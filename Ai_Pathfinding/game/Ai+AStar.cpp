#include <iostream>
#include "Ai.h"

void Ai::AStar(Node* start, Node* end)
{
    if (_state == AiState::waiting)
    {
        aStarTracedPath.clear();
        aStarFoundEnd = false;
        aStarEndTrace = nullptr;
        drawAStarIndex = 0;

        for (auto& row : grid)
        {
            for (auto& node : row)
            {
                node.Reset(true);
            }
        }

        while (!aStarOpenSet.empty()) { aStarOpenSet.pop(); }
        start->gCost = 0;
        aStarOpenSet.push(start);
        start->visited = true;

        _state = AiState::aStar;
        return;
    }

    if (aStarFoundEnd)
    {
        if (aStarEndTrace != nullptr && aStarEndTrace != start)
        {
            aStarTracedPath.emplace_back(aStarEndTrace);
            aStarEndTrace = aStarEndTrace->parent;
        }
        else
        {
            std::reverse(aStarTracedPath.begin(), aStarTracedPath.end());
            drawAStarIndex = 0;
            _state = AiState::traceAStar;
        }
        return;
    }

    if (!aStarOpenSet.empty())
    {
        Node* current = aStarOpenSet.top();
        aStarOpenSet.pop();

        if (current != start && current != end)
        {
            current->fillColor = ASTAR_COLOR;
            current->StartAnim();
        }

        if (current == end)
        {
            aStarFoundEnd = true;
            aStarEndTrace = end;
            std::cout << "AStar path found!\n";
            return;
        }

        for (auto neighbor : GetNeighbors(current))
        {
            if (neighbor->blocked && neighbor != end)
            {
                continue;
            }

            float tentativeCost = current->gCost + 1;
            if (tentativeCost < neighbor->gCost)
            {
                neighbor->gCost = tentativeCost;

                Heuristic heuristic;
                neighbor->hCost = heuristic(neighbor, end);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;

                neighbor->parent = current;
                neighbor->step = current->step + 1;
                aStarOpenSet.push(neighbor);
            }
        }
    }
    else
    {
        std::cout << "No AStar path!\n";
        _state = AiState::waiting;
    }

}