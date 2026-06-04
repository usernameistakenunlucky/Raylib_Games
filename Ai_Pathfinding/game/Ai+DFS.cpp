#include <stack>
#include <iostream>
#include "Ai.h"

void Ai::DFS(Node* start, Node* end)
{
    if (_state == AiState::waiting)
    {
        dfsTracedPath.clear();
        dfsFoundEnd = false;
        dfsEndTrace = nullptr;
        drawDFSindex = 0;

        for (auto& row : grid)
        {
            for (auto& node : row)
            {
                node.Reset(true);
            }
        }

        while (!dfsOpenSet.empty()) { dfsOpenSet.pop(); }
        dfsOpenSet.push(start);
        start->visited = true;

        _state = AiState::DFS;
        return;
    }

    if (dfsFoundEnd)
    {
        if (dfsEndTrace != nullptr && dfsEndTrace != start)
        {
            dfsTracedPath.emplace_back(dfsEndTrace);
            dfsEndTrace = dfsEndTrace->parent;
        }
        else
        {
            std::reverse(dfsTracedPath.begin(), dfsTracedPath.end());
            drawDFSindex = 0;
            _state = AiState::traceDFS;
        }
        return;
    }

    if (!dfsOpenSet.empty())
    {
        Node* current = dfsOpenSet.top(); 
        dfsOpenSet.pop();

        if (current != start && current != end)
        {
            current->fillColor = DFS_COLOR;
            current->StartAnim();
        }

        for (Node* neighbor : GetNeighbors(current))
        {
            if ((neighbor->blocked || neighbor->visited) && neighbor != end) { continue; }

            neighbor->parent = current;
            neighbor->step = current->step + 1;
            neighbor->visited = true;

            if (neighbor == end)
            {
                dfsFoundEnd = true;
                dfsEndTrace = end;
                std::cout << "DFS path was found\n";
                return;
            }

            dfsOpenSet.push(neighbor);
        }
    }
    else
    {
        std::cout << "DFS path NOT found!\n";
        _state = AiState::waiting;
    }
}