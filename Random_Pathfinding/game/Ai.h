#pragma once
#include "raylib.h"
#include "Node.h"
#include <vector>

class Ai
{
public:

	std::vector<std::vector<Node>> grid;
	Node* start = nullptr;
	Node* end = nullptr;

	Ai() {}

	void Main();
	void Start();
	void Restart();
	void UpdateAll();
	void RenderAll();
	void Interaction();

	Node* GetRandomNode();
	std::vector<Node*> GetNeighbours(Node* node);

	void BFS(Node* a, Node* B);
	void DFS(Node* a, Node* B);
	void Djikstra(Node* a, Node* B);
	void AStar(Node* a, Node* B);

	void RandomSearch(Node* start, Node* end);
	std::vector<Node*> currentPath;
	std::vector<Node*> currentVisited;
	bool searchComplete = false;

};