#include "Ai.h"

//void Ai::RandomSearch(Node* start, Node* end)
//{
//	Node* current = start;
//	std::vector<Node*> currentPath;
//	std::vector<Node*> visited;
//	currentPath.push_back(current);
//	visited.push_back(current);
//
//	while (current != end)
//	{
//		std::vector<Node*> neighbours = GetNeighbours(current);
//		int randIndex = GetRandomValue(0, neighbours.size() - 1);
//		for (Node* neightbours : )
//	}
//
//}

void Ai::RandomSearch(Node* start, Node* end)
{
	if (searchComplete) { return; }

	if (currentPath.empty())
	{
		currentPath.push_back(start);
		currentVisited.push_back(start);
	}

	Node* current = currentPath.back();

	if (current == end)
	{
		int step = 1;
		for (Node* n : currentPath)
		{
			if (n != start && n != end)
			{
				n->fillColor = GOLD;
				n->displayText = std::to_string(step);
				step++;
			}
		}
		searchComplete = true;
		return;
	}

	std::vector<Node*> neighbours = GetNeighbours(current);

	std::vector<Node*> unvisited;
	for (Node* n : neighbours)
	{
		bool alreadyVisited = false;
		for (Node* v : currentVisited)
		{
			if (v == n) { alreadyVisited = true; break; }
		}
		if (!alreadyVisited) { unvisited.push_back(n); }
	}

	if (unvisited.empty())
	{
		for (Node* n : currentPath)
		{
			if (n != start && n != end)
			{
				int r = (int)n->fillColor.r /* - DARKEN_RATE*/;
				int g = (int)n->fillColor.g - DARKEN_RATE;
				int b = (int)n->fillColor.b - DARKEN_RATE;
				if (r < GRAY.r) { r = GRAY.r; }
				if (g < 0) { g = 0; }
				if (b < 0) { b = 0; }
				n->fillColor = Color{ (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
			}
		}
		currentPath.clear();
		currentVisited.clear();
		return;
	}

	int randIndex = GetRandomValue(0, unvisited.size() - 1);
	current = unvisited[randIndex];
	currentPath.push_back(current);
	currentVisited.push_back(current);
}