#pragma once
#include "raylib.h"
#include "Node.h"
#include "Definitions.h"
#include <vector>
#include <queue>
#include <stack>

class Ai
{
public:

	AiState _state = AiState::waiting;

	std::vector<std::vector<Node>> grid;
	Node* startPoint = nullptr;
	Node* endPoint = nullptr;

	Ai() {}

	void Main();
	void Start();
	void Restart();
	void UpdateAll();
	void RenderAll();
	void Interaction();

	Node* GetRandomNode();
	std::vector<Node*> GetNeighbors(Node* node);

	// BFS /////////////////////////////////////
	void BFS(Node* start, Node* end);
	std::vector<Node*> bfsTracedPath;
	std::queue<Node*> bfsOpenSet;
	bool bfsFoundEnd = false;
	Node* bfsEndTrace = nullptr;
	int drawBFSindex = 0;
	////////////////////////////////////////////
	// DFS /////////////////////////////////////
	void DFS(Node* start, Node* end);
	std::vector<Node*> dfsTracedPath;
	std::stack<Node*> dfsOpenSet;
	bool dfsFoundEnd = false;
	Node* dfsEndTrace = nullptr;
	int drawDFSindex = 0;
	////////////////////////////////////////////
	// Djikstra ////////////////////////////////
	void Djikstra(Node* start, Node* end);
	std::vector<Node*> djikstraTracedPath;

	struct Compare // functor instead of lambda so i can use in header...
	{
		bool operator()(Node* a, Node* b)
		{
			return a->gCost > b->gCost;
		}
	};
	std::priority_queue<Node*, std::vector<Node*>, Compare> djikstraOpenSet;

	bool djikstraFoundEnd = false;
	Node* djikstraEndTrace = nullptr;
	int drawDjikstraIndex = 0;
	////////////////////////////////////////////
	// AStar ////////////////////////////////
	void AStar(Node* start, Node* end);
	std::vector<Node*> aStarTracedPath;

	struct Heuristic 
	{
		float operator()(Node* a, Node* b)
		{
			return abs(a->gridX - b->gridX) + abs(a->gridY - b->gridY);
		}
	};
	struct CompareAStar 
	{
		bool operator()(Node* a, Node* b)
		{
			return a->fCost > b->fCost || (a->fCost == b->fCost && a->hCost > b->hCost);
		}
	};
	std::priority_queue<Node*, std::vector<Node*>, CompareAStar> aStarOpenSet;

	bool aStarFoundEnd = false;
	Node* aStarEndTrace = nullptr;
	int drawAStarIndex = 0;
	////////////////////////////////////////////
	////////////////////////////////////////////

	void RandomSearch(Node* start, Node* end);
	std::vector<Node*> currentPath;
	std::vector<Node*> currentVisited;
	bool searchComplete = false;

};